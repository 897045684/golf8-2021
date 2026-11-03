#!/usr/bin/bash -e

BUILD_DIR=/data/openpilot
cd $BUILD_DIR
git init
git remote set-url --push origin http://192.168.3.203:8418/mawei/lukasloetkolben.git

# Cleanup
find . -name '*.a' -delete
find . -name '*.o' -delete
find . -name '*.os' -delete
find . -name '*.pyc' -delete
find . -name 'moc_*' -delete
find . -name '__pycache__' -delete
rm -rf .sconsign.dblite Jenkinsfile release/
rm selfdrive/modeld/models/*.onnx
touch prebuilt

# Add built files to git
git add -f .

VERSION="mqb2026"
git commit -m "mqb2026"
git branch -m  "mqb2026"
git push -f --no-verify origin "mqb2026"
