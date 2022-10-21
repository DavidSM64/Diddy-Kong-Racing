if [[ $1 == '--update-readme' ]]; then
  export NEW_SCORE=$(python3 ./tools/python/score.py)
  echo $NEW_SCORE
  python3 - <<'EOF' > README.md.tmp
import sys
import os
import re
BEGIN='<!-- README_SCORE_BEGIN -->'
END='<!-- README_SCORE_END -->'
print(
  re.sub(
    fr'(?s).{BEGIN}.*{END}',
    f'\n{BEGIN}\n{os.environ["NEW_SCORE"]}\n{END}',
    open('README.md', 'r').read()
  )
)
EOF
mv README.md.tmp README.md
else
  python3 ./tools/python/score.py "$@"
fi
