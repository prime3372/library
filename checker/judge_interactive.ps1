# arguments
$sol = $Args[0]
$gen = $Args[1]

# constants
$casesnum = 20

do {

  g++ $sol -o sol.exe -O2 -std=c++23 -Wall -Wextra; if ($LASTEXITCODE -ne 0) { break }
  g++ $gen -o gen.exe -O2 -std=c++23 -Wall -Wextra; if ($LASTEXITCODE -ne 0) { break }

  for ($i = 1; $i -le $casesnum; $i++) {
    python checker/interactor.py ".\\gen.exe" ".\\sol.exe"
    if ($LASTEXITCODE -eq 0) {
      Write-Host "Test" $i "AC" -ForegroundColor Green
      continue
    }
    if ($LASTEXITCODE -eq 1) {
      Write-Host "Test" $i "WA" -ForegroundColor Red
    } elseif ($LASTEXITCODE -eq 2) {
      Write-Host "Test" $i "RE" -ForegroundColor Magenta
    } elseif ($LASTEXITCODE -eq 3) {
      Write-Host "Test" $i "TLE" -ForegroundColor Yellow
    } else {
      Write-HOST "Test" $i "FAIL" -ForegroundColor Blue
    }
    code in.txt out.txt
    break
  }

} while ($false)

Remove-Item sol.exe -ErrorAction SilentlyContinue
Remove-Item gen.exe -ErrorAction SilentlyContinue