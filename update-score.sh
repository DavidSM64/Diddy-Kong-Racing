#!/usr/bin/env bash

export NEW_SCORE="$(python3 ./tools/python/score.py)"
export NEW_SCORE_SUMMARY="$(python3 ./tools/python/score.py --summary)"

python3 - <<'EOF' > README.md.tmp
import sys
import os
import re
from datetime import datetime

BEGIN = '<!-- README_SCORE_BEGIN -->'
END = '<!-- README_SCORE_END -->'
BEGIN_SUMMARY = '<!-- README_SCORE_SUMMARY_BEGIN -->'
END_SUMMARY = '<!-- README_SCORE_SUMMARY_END -->'
DATE_STR = datetime.now().strftime('As of %B %-d, %Y, this is our current score:')

score_updated = re.sub(
  fr'(?s).{BEGIN}.*{END}',
  f'\n{BEGIN}\n{DATE_STR}\n```\n{os.environ["NEW_SCORE"]}\n```\n{END}',
  open('README.md', 'r').read()
)

tabbed_summary = '\n'.join(['\t' + line for line in os.environ["NEW_SCORE_SUMMARY"].split('\n')])

summary_updated = re.sub(
  fr'(?s).{BEGIN_SUMMARY}.*{END_SUMMARY}',
  f'\n{BEGIN_SUMMARY}\n{DATE_STR}\n{tabbed_summary}\n{END_SUMMARY}',
  score_updated
)
print(summary_updated, end='')
EOF
mv README.md.tmp README.md
