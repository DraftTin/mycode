# Linux Learning Note

## tr
The tr command is a UNIX command-line utility for translating or deleting characters. It supports a range of transformations including uppercase to lowercase, squeezing repeating characters, deleting specific characters, and basic find and replace. It can be used with UNIX pipes to support more complex translation. tr stands for translate. 
``` bash
echo "{123}" | tr "{}" "()"         # -> (123)

echo "1233334444" | tr -s "34"      # -> 1234

echo "1233334444" | tr -s "34" "56" # -> 1256

echo "1233334444" | tr -d "34"     # -> 12
```

## sort
sort FILE
```bash
sort -r

sort 
```

## uniq
uniq is the tool that helps to detect the adjacent duplicate lines and also deletes the duplicate lines.

```bash
cat words.txt | tr -s ' ' '\n' | sort | uniq -c # calc word frequency
```

## grep
**grep** is used to search text and strings in a given file.
```bash
grep -E # --extended-regexp
```

## awk

Useful For: 
(a) Transform data files 
(b) Produce formatted reports 

**Syntax:**

awk options 'selection _criteria {action }' input-file > output-file
