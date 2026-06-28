# arguments
$sol = $Args[0]
$gen = $Args[1]

do {

  g++ $sol -o sol.exe -O2 -std=c++23 -Wall -Wextra; if ($LASTEXITCODE -ne 0) { break }
  g++ $gen -o gen.exe -O2 -std=c++23 -Wall -Wextra; if ($LASTEXITCODE -ne 0) { break }

  for ($i = 1; $i -le 20; $i++) {
    python checker/interactive.py ".\\gen.exe" ".\\sol.exe"
    if ($LASTEXITCODE -ne 0) {
      Write-Host "Test" $i "WA"
      code in.txt out.txt
      break
    }
    Write-Host "Test" $i "AC"
  }

} while ($false)

Remove-Item sol.exe -ErrorAction SilentlyContinue
Remove-Item gen.exe -ErrorAction SilentlyContinue