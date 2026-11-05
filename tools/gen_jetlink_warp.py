"""生成 jetlink 期望格式的 driving warp：{'run': TinyJit, 'input_specs': {...}}"""
import pickle
import numpy as np
from tinygrad import Tensor, TinyJit

from openpilot.selfdrive.modeld.compile_warp import make_frame_prepare
from openpilot.selfdrive.modeld.constants import ModelConstants
from openpilot.system.camerad.cameras.nv12_info import get_nv12_info

CAM_W, CAM_H = 1928, 1208
MODEL_W, MODEL_H = 512, 256
OUT = "/data/openpilot/selfdrive/modeld/models/driving_warp_1928x1208_tinygrad.pkl"

stride, y_height, uv_height, frame_size = get_nv12_info(CAM_W, CAM_H)
print("nv12:", stride, y_height, uv_height, frame_size)

prepare = make_frame_prepare(CAM_W, CAM_H, MODEL_W, MODEL_H)


def warp2(M_inv, input_frame):
  a = prepare(input_frame[0], M_inv[0])
  b = prepare(input_frame[1], M_inv[1])
  return Tensor.stack(a, b)


jit = TinyJit(warp2)
frames = np.zeros((2, frame_size), dtype=np.uint8)
tfm = np.zeros((2, 3, 3), dtype=np.float32)
t_frames = Tensor(frames)
t_tfm = Tensor(tfm)
for _ in range(3):
  out = jit(M_inv=t_tfm, input_frame=t_frames)
  out.realize()

cap = jit.captured
print("expected_names:", list(getattr(cap, "expected_names", [])))
print("ret shape:", tuple(getattr(cap.ret, "shape", ())))
specs = {
  "M_inv": (tuple(tfm.shape), np.float32, t_tfm.device),
  "input_frame": (tuple(frames.shape), np.uint8, t_frames.device),
}
pickle.dump({"run": jit, "input_specs": specs}, open(OUT, "wb"))
print("saved", OUT, specs)
