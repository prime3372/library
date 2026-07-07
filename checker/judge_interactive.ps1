# arguments
$sol = $Args[0]
$gen = $Args[1]
$inc = $Args[2]

# constants
$casesnum = 20

do {

  g++ $sol -I $inc -O2 -o sol.exe -std=c++23 -Wall -Wextra
  if ($LASTEXITCODE -ne 0) {
    Write-Host "CE" -ForegroundColor Cyan
    code $sol
    break
  }

  g++ $gen -I $inc -O2 -o gen.exe -std=c++23 -Wall -Wextra
  if ($LASTEXITCODE -ne 0) {
    Write-Host "FAIL" "Compile Error" $gen -ForegroundColor Blue
    code $gen
    break
  }

  for ($i = 1; $i -le $casesnum; $i++) {
    py checker/interactor.py "sol.exe" "gen.exe" $i
    if ($LASTEXITCODE -ne 0) {
      code in.txt out.txt
      break
    }
  }

} while ($false)

Remove-Item sol.exe -ErrorAction SilentlyContinue
Remove-Item gen.exe -ErrorAction SilentlyContinue