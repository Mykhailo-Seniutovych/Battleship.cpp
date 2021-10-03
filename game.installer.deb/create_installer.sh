set -e 
version=1.0.0
mkdir -p battleship++_${version}_amd64/usr/bin/battleship++
cp ../game/build/bin/map.txt ../game/build/bin/app-config.json ../game/build/bin/battleship++ battleship++_${version}_amd64/usr/bin/battleship++
dpkg-deb --build --root-owner-group battleship++_${version}_amd64
