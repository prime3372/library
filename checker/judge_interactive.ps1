# arguments
$sol = $Args[0]
$gen = $Args[1]

# constants
$casesnum = 20

do {

  g++ $sol -o sol.exe -O2 -std=c++23 -Wall -Wextra; if ($LASTEXITCODE -ne 0) { break }
  g++ $gen -o gen.exe -O2 -std=c++23 -Wall -Wextra; if ($LASTEXITCODE -ne 0) { break }

  for ($i = 1; $i -le $casesnum; $i++) {
    python checker/interactor.py ".\\gen.exe" ".\\sol.exe" $i
    if ($LASTEXITCODE -ne 0) {
      code in.txt out.txt
      break
    }
  }

} while ($false)

Remove-Item sol.exe -ErrorAction SilentlyContinue
Remove-Item gen.exe -ErrorAction SilentlyContinue