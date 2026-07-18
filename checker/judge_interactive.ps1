# arguments
$sol = $Args[0]
$gen = $Args[1]
$inc = $Args[2]

# constants
$casesnum = 50

do {

  Write-Host "compiling..."

  g++ $sol -o sol.exe -I $inc -O2 -Wall -Wextra -fdiagnostics-color=always -std=c++23
  if ($LASTEXITCODE -ne 0) {
    Write-Host "CE" -ForegroundColor Cyan
    if (Test-Path $sol) { code $sol }
    break
  }

  g++ $gen -o gen.exe -I $inc -O2 -Wall -Wextra -fdiagnostics-color=always -std=c++23
  if ($LASTEXITCODE -ne 0) {
    Write-Host "FAIL" "Compile Error" $gen -ForegroundColor Blue
    if (Test-Path $gen) { code $gen }
    break
  }

  Write-Host "compilation finished"

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