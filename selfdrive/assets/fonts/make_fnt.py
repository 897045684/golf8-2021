#!/usr/bin/env python3
"""把矢量 CJK 字体烘焙成 raylib 可读的 AngelCode BMFont（.fnt + .png）。

输出格式严格对齐仓库里 selfdrive/assets/fonts/process.py 的产物：
  info size=-<size> ... / common lineHeight=<size> base=<ascent> / page / chars / char ...
raylib 用 common.lineHeight 作为 font.baseSize，所以 lineHeight 必须等于渲染字号。

用法：
  python3 make_fnt.py --font NotoSansSC-Regular.otf --size 88 --out ../selfdrive/assets/fonts
"""
import argparse
import json
import math
import os
import sys

from PIL import Image, ImageDraw, ImageFont

EXTRA_CHARS = "–‑✓×°§•X⚙✕◀▶✔⌫⇧␣○●↳çêüñ€£¥"
CN_PUNCT = "，。！？；：、“”‘’（）《》【】…—·～"
PADDING = 6


def charset_from_translations(trans_dir: str, extra: str = "", only_langs=None) -> str:
  chars = set(chr(c) for c in range(32, 127)) | set(EXTRA_CHARS) | set(CN_PUNCT) | set(extra)
  if os.path.isdir(trans_dir):
    langs = os.path.join(trans_dir, "languages.json")
    if os.path.isfile(langs):
      chars |= set("".join(json.load(open(langs, encoding="utf-8")).keys()))
    for name in os.listdir(trans_dir):
      if not name.endswith(".po"):
        continue
      if only_langs and not any(name == f"app_{l}.po" for l in only_langs):
        continue
      chars |= set(open(os.path.join(trans_dir, name), encoding="utf-8").read())
  chars -= set("\n\r\t")
  return "".join(sorted(chars))


def classify(code: int) -> str:
  return "cjk"


def render_glyph(font: ImageFont.FreeTypeFont, ch: str):
  """返回 (mask_img, w, h, xoffset, yoffset_rel_baseline)。以基线为参考。"""
  try:
    x0, y0, x1, y1 = font.getbbox(ch, anchor="ls")
  except Exception:
    return None
  w, h = x1 - x0, y1 - y0
  if w <= 0 or h <= 0:
    return None
  mask = Image.new("L", (w, h), 0)
  ImageDraw.Draw(mask).text((-x0, -y0), ch, font=font, fill=255, anchor="ls")
  return mask, w, h, x0, y0


def main() -> int:
  ap = argparse.ArgumentParser()
  ap.add_argument("--font", required=True)
  ap.add_argument("--size", type=int, default=88)
  ap.add_argument("--out", required=True)
  ap.add_argument("--trans-dir", default="")
  ap.add_argument("--atlas-width", type=int, default=4096)
  ap.add_argument("--name", default="")
  ap.add_argument("--only-langs", default="", help="逗号分隔，如 zh-CHS,zh-CHT")
  args = ap.parse_args()

  size = args.size
  face = args.name or os.path.splitext(os.path.basename(args.font))[0]
  font = ImageFont.truetype(args.font, size)
  ascent, descent = font.getmetrics()

  only = [x for x in args.only_langs.split(",") if x] or None
  text = charset_from_translations(args.trans_dir, only_langs=only) if args.trans_dir else charset_from_translations("")
  chars, skipped = [], []
  for ch in text:
    missing = font.getmask(ch, mode="L").getbbox() is None and ch.strip() != ""
    if missing:
      skipped.append(ch)
      continue
    chars.append(ch)

  # shelf packing
  pad = PADDING
  cells = []
  for ch in chars:
    g = render_glyph(font, ch)
    if g is None:
      if ch != " ":
        skipped.append(ch)
      cells.append((ch, None, int(round(font.getlength(ch)))))
      continue
    mask, w, h, x0, y0 = g
    cells.append((ch, (mask, w, h, x0, y0), int(round(font.getlength(ch)))))

  aw = args.atlas_width
  shelf_h, shelves, placements = 0, [], []
  x = pad
  y = pad
  for ch, g, adv in cells:
    if g is None:
      placements.append((ch, None, adv))
      continue
    _, w, h, _, _ = g
    if x + w + pad > aw:
      y += shelf_h + pad
      x = pad
      shelf_h = 0
    placements.append((ch, (x, y), adv))
    x += w + pad
    shelf_h = max(shelf_h, h)
  ah = y + shelf_h + pad
  ah = 1 << max(9, (ah - 1).bit_length())

  atlas = Image.new("RGBA", (aw, ah), (255, 255, 255, 0))
  entries = []
  for ch, pos, adv in placements:
    if pos is None:
      entries.append(dict(id=ord(ch), x=0, y=0, width=0, height=0, xoffset=0, yoffset=0, xadvance=adv))
      continue
    (gx, gy) = pos
    g = next(c[1] for c in cells if c[0] == ch)
    mask, w, h, x0, y0 = g
    atlas.paste((255, 255, 255, 255), (gx, gy), mask)
    entries.append(dict(id=ord(ch), x=gx, y=gy, width=w, height=h,
                        xoffset=x0, yoffset=ascent + y0, xadvance=adv))

  os.makedirs(args.out, exist_ok=True)
  png_name = f"{face}.png"
  atlas.save(os.path.join(args.out, png_name))

  lines = [
    f'info face="{face}" size=-{size} bold=0 italic=0 charset="" unicode=1 stretchH=100 smooth=0 aa=1 padding=0,0,0,0 spacing=0,0 outline=0',
    f'common lineHeight={size} base={ascent} scaleW={aw} scaleH={ah} pages=1 packed=0 alphaChnl=0 redChnl=4 greenChnl=4 blueChnl=4',
    f'page id=0 file="{png_name}"',
    f"chars count={len(entries)}",
  ]
  for e in sorted(entries, key=lambda e: e["id"]):
    lines.append(("char id={id:<6}x={x:<6}y={y:<6}width={width:<6}height={height:<6}"
                  "xoffset={xoffset:<6}yoffset={yoffset:<6}xadvance={xadvance:<6}page=0  chnl=15").format(**e))
  fnt_path = os.path.join(args.out, f"{face}.fnt")
  open(fnt_path, "w", encoding="utf-8").write("\n".join(lines) + "\n")

  print(f"{face}: glyphs={len(entries)} atlas={aw}x{ah} ({aw*ah*4/1e6:.1f} MB) "
        f"png={os.path.getsize(os.path.join(args.out, png_name))/1e6:.2f} MB skipped={len(skipped)}")
  if skipped:
    print("  无可绘制字形:", "".join(sorted(set(skipped)))[:40])
  return 0


if __name__ == "__main__":
  sys.exit(main())
