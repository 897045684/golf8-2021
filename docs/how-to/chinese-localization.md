# 简体中文本地化与 CJK 字体

本分支的中文界面由两部分组成：**翻译目录**（.po）与 **CJK 位图字体**。

## 1. 翻译目录

- 语言列表：`selfdrive/ui/translations/languages.json`（`中文（简体）` → `zh-CHS`）
- 目录文件：`selfdrive/ui/translations/app_zh-CHS.po`，共 723 条 msgid，全部已翻译
- 运行时加载：`system/ui/lib/multilang.py` 直接解析 .po（不编译 .mo），`tr()` 精确匹配 msgid

覆盖来源：

| 来源 | 说明 |
|---|---|
| `tr("...")` | `selfdrive/ui/**`、`system/ui/**` 全部调用 |
| 控件字面量 | `BigButton("toggles")`、`.set_text("...")`、`options=[...]` 等不经过 tr 的字符串，由 `UnifiedLabel.text` 统一走 `tr()` |
| 行驶提示 | `selfdrive/selfdrived/events.py` 里 `*Alert("...")` 文案，经 label 渲染时翻译 |

重新抽取（新增字符串后）：

```bash
# 设备或 Linux 上，依赖 openpilot 运行环境
PYTHONPATH=/data/openpilot python3 selfdrive/ui/update_translations.py
```

注意：`update_translations.py` 现在扫描**整个** `selfdrive/ui` + `system/ui`（旧版只扫 4 个子目录，导致 mici / sunnypilot 页面漏翻）。

## 2. CJK 字体

语言 `zh-CHS` / `zh-CHT` 会走 `multilang.requires_cjk_font()`，使用：

- `NotoSansSC-Regular.fnt/.png`（72px 基准，979 字形）
- `NotoSansSC-Bold.fnt/.png`
- 对应子集字体 `NotoSansSC-*.otf`（仅用于重新生成图集，OFL 许可）

字重映射（`system/ui/lib/application.py` 的 `CJK_ALIAS`）：

```
LIGHT/NORMAL/MEDIUM/ROMAN/DISPLAY_REGULAR -> CJK_REGULAR
BOLD/SEMI_BOLD/DISPLAY/AUDIOWIDE          -> CJK_BOLD
UNIFONT                                    -> 仍用 unifont（语言选择列表等）
```

中文界面只加载 2 个 CJK 图集 + unifont，跳过整套 Inter（约省 80 MB 显存）。

### 重新生成图集

离线生成（不需要 raylib，Pillow 即可）：

```bash
python3 selfdrive/assets/fonts/make_fnt.py \
  --font selfdrive/assets/fonts/NotoSansSC-Regular.otf \
  --size 72 --atlas-width 4096 \
  --trans-dir selfdrive/ui/translations --only-langs zh-CHS,zh-CHT \
  --out selfdrive/assets/fonts
```

或走仓库原有流程（需要 pyray）：`python3 selfdrive/assets/fonts/process.py`，它会自动把 `NotoSansSC*` 按 72px + 中文 po 字符集处理。

### 字集与缺字

字形集 = ASCII + 中文标点 + `app_zh-CHS.po` / `app_zh-CHT.po` 中出现的全部字符（约 979 个）。
界面上出现目录之外的汉字（如 Wi-Fi 名、自定义软件名）会显示为方框，需要时把更多字符加进 po 或改用 GB2312 全量字符集重新生成（图集会变成 4096×4096，约 67 MB/字重）。

emoji（如 🔥）不进入字体图集，由 `system/ui/lib/emoji.py` 的 emoji 纹理单独渲染。
