#!/bin/sh

mkdir -p opk
cp ./vvv_sdl12.elf opk/vvv_sdl12.elf
cp ./vvvvvv.png opk/icon.png
cp ./data.zip opk/data.zip

# https://unix.stackexchange.com/questions/219268/how-to-add-new-lines-when-using-echo
print()
	case    ${IFS- } in
	(\ *)   printf  %b\\n "$*";;
	(*)     IFS=\ $IFS
	printf  %b\\n "$*"
	IFS=${IFS#?}
esac

# Create GmenuNx entry file plus other things

print '[Desktop Entry]
Type=Application
Name=VVVVVV
Comment=Needs data.zip in /usr/local/home/.vvvvvv
Exec=vvv_sdl12.elf
Icon=icon
Terminal=false
Type=Application
Categories=games;
X-OD-NeedsDownscaling=true
' > opk/default."$1".desktop

mksquashfs ./opk vvvvvv_"$1".opk -all-root -noappend -no-exports -no-xattrs

rm -r opk
