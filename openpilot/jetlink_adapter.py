"""Jetlink <-> 本 fork（evo-release，sunnypilot 系）的适配层。

按 jetlink docs/porting.md 的约定：
  * manager 用本模块构造进程列表，并以 jetlinkd 身份运行 gadget owner
  * 所有放在 modeld / selfdrived / hardwared / UI 的 hook 都经 hooks() 调进来
  * 顶层只 import 标准库，重依赖放在函数里
"""
import functools
import os

API = 3              # 本 adapter 对应的 jetlink.openpilot API 版本
OWNER = 'jetlinkd'   # manager 里 gadget owner 的进程名


def _cereal_alias():
  """jetlink 内部按 openpilot.cereal 引用 cereal；本分支是顶层 cereal，做个别名。"""
  import sys
  try:
    import cereal
    sys.modules.setdefault('openpilot.cereal', cereal)
  except Exception:
    pass


def _adapter_class():
  _cereal_alias()
  from jetlink.openpilot.stock import Stock

  class Adapter(Stock):
    """evo-release 与 stock 0.11 的差异都写在这里。"""

    # 本分支 scons 生成的是 warp_<w>x<h>_tinygrad.pkl（没有 driving_ 前缀）
    WARP_NAME = 'warp_{cam_w}x{cam_h}_tinygrad.pkl'

    # 本分支多一个 selfdriveStateSP（MADS），判断"是否在控制中"要看它
    IN_CONTROL_SERVICES = ('carState', 'carControl', 'selfdriveState', 'selfdriveStateSP')

    # warp 在仓库根的 selfdrive/modeld/models（stock 在 openpilot/selfdrive/...）
    WARP_DIR = 'selfdrive/modeld/models'

    def camera(self):
      """stock 从 openpilot.common.hardware 取设备类型；本分支在 openpilot.system.hardware。"""
      from openpilot.system.hardware import HARDWARE
      from openpilot.common.transformations.camera import _ar_ox_fisheye, _os_fisheye
      from openpilot.common.transformations.model import MEDMODEL_INPUT_SIZE
      camera = _os_fisheye if HARDWARE.get_device_type() == 'mici' else _ar_ox_fisheye
      return camera.width, camera.height, *MEDMODEL_INPUT_SIZE

    def model_root(self):
      """本分支的 Paths 在 openpilot.system.hardware（stock 在 openpilot.common.hardware）。"""
      from pathlib import Path
      from openpilot.system.hardware.hw import Paths
      return Path(Paths.model_root())

    def engaged(self, sm) -> bool:
      """MADS 只开横向（ACC 未接管）也算在控制中，换模型时才不会被误判为未启用。"""
      try:
        if sm['selfdriveState'].enabled or sm['selfdriveStateSP'].mads.enabled:
          return True
      except Exception:
        pass
      return super().engaged(sm)

  return Adapter


def adapter():
  return _adapter_class()()


def owner_config():
  return _adapter_class().owner_config()


def main():
  _adapter_class().main()


def link_on() -> bool:
  """读 JetlinkLink 参数文件；没有 jetlink 也能用（不 import 任何东西）。"""
  prefix = os.environ.get('OPENPILOT_PREFIX', '')
  root = os.environ.get('PARAMS_ROOT') or ('/data/params' if os.path.isfile('/AGNOS') else
                                           os.path.expanduser(f'~/.comma{prefix}/params'))
  try:
    with open(os.path.join(root, os.environ.get('OPENPILOT_PREFIX', 'd'), 'JetlinkLink')) as f:
      return f.read().strip() not in ('', '0')
  except OSError:
    return False


def _cloudlog():
  from openpilot.common.swaglog import cloudlog
  return cloudlog


@functools.cache
def hooks():
  """每个进程一份，永不抛异常。"""
  try:
    from jetlink.openpilot.hooks import Hooks
    return Hooks(API, adapter, link_on=link_on, log=_cloudlog)
  except Exception as e:
    try:
      from jetlink.openpilot.hooks import Off
    except Exception:
      return _NoJetlink(f"jetlink is missing: {e}")
    return Off(str(e), link_on=link_on)


def should_run(started, params, CP) -> bool:
  return hooks().should_run(started, params, CP)


class _NoJetlink:
  """jetlink 代码缺失时，所有 hook 都按"链路关闭"回答，绝不影响 openpilot 本体。"""

  def __init__(self, why):
    self._why = why

  def should_run(self, started, params, CP):
    return False

  def status(self):
    return None

  def reason(self):
    return self._why if link_on() else None

  def prepare(self, chestnut):
    return False

  def handed_over(self, model):
    return False

  def state(self, model):
    return 'none'

  def shutdown_step(self, should_shutdown, reason=''):
    return should_shutdown

  def runtime(self):
    return None

  def swap_events(self, tick_s):
    return None
