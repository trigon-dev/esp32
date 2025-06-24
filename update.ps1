param(
  [string] $Repo      = "trigon-dev/esp32",
  [string] $AssetName = "loader.exe",
  [string] $LocalExe  = ".\loader.exe"
)

function Get-Latest { Invoke-RestMethod -UseBasicParsing "https://api.github.com/repos/$Repo/releases/latest" }
function Download($url,$dest){ Invoke-WebRequest -UseBasicParsing $url -OutFile $dest }

$rel = Get-Latest; $tag = $rel.tag_name
$asset = $rel.assets | Where-Object { $_.name -eq $AssetName }
$tmp = "$LocalExe.download"

Download $asset.browser_download_url $tmp
if (Test-Path $LocalExe) { Copy-Item $LocalExe "$LocalExe.bak" -Force }
Move-Item $tmp $LocalExe -Force

Start-Process -FilePath $LocalExe
