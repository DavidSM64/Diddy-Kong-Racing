#!/usr/bin/env bash
export NEW_SCORE="$(python3 ./tools/python/score.py)"
python3 - <<'EOF' > README.md.tmp
import sys
import os
import re
from datetime import datetime

BEGIN = '<!-- README_SCORE_BEGIN -->'
END = '<!-- README_SCORE_END -->'
DATE_STR = datetime.now().strftime('As of %B %-d, %Y, this is our current score:')
print(
  re.sub(
    fr'(?s).{BEGIN}.*{END}',
    f'\n{BEGIN}\n{DATE_STR}\n```\n{os.environ["NEW_SCORE"]}\n```\n{END}',
    open('README.md', 'r').read()
  ),
  end=''
)
EOF
mv README.md.tmp README.md
