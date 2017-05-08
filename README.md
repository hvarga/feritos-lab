## Razvoj prilagodene Linux distribucije u sklopu projekta Yocto

### Sadrzaj laboratorijske vjezbe

Vjezba je podjeljena na dva dijela. Prvi dio govori o Yocto projektu te diskutira o potrebnim koracima za izradu firmware za Raspberry Pi. Drugi dio se bazira na debugging aplikacija pisanih u programskom jeziku C te o potrebnim alatima i vjestinama.

U prvom djelu ce se studentima dati pristup vec unaprijed pripremljeni firmware i SDK. Studenti nece morati sami podesavat Yocto te izradivati firmware i SDK. Razlog tome je sto se na samoj izradi gubi pozamasna kolicina vremena. Unatoc tome, studenti ce pak morati sami instalirati firmware na Raspberry Pi i dovesti ga do stanja u kojem je Raspberry Pi spreman za drugi dio vjezbe.

#### Konfiguracija Yocto projekta

Za punu kompatibilnost, Yocto projekt zahtjeva sljedece komponente:

- Operacijski sustav. Tocna lista podrzanih operacijskih sustava se moze vidjeti na http://www.yoctoproject.org/docs/2.2.1/ref-manual/ref-manual.html#detailed-supported-distros.
- Potrebiti softverski paketi instalirani na operacijskom sustavu. Tocna lista svih paketa za sve podrzane operacijske sustave se moze vidjeti na http://www.yoctoproject.org/docs/2.2.1/ref-manual/ref-manual.html#required-packages-for-the-host-development-system.

Bez gore navedenih komponenti, postoji velika mogucnost da Yocto nece biti u stanju napraviti firmware ili da taj firmware nece biti u potpunosti stabilan. Dakle, potrebno se drzati iskljucivo gornjih uputa. Najbolji nacin da bi se to postiglo je koristeci Docker napisan iskljucivo za Yocto potrebe. Za potrebe vjezbe, napisan je Dockerfile dostupan [Dockerfile](Dockerfile). Iz Dockerfile se moze napraviti Docker Image koji ce onda sluziti da bi se u konacnici mogao startati Docker Container u kojem se onda moze koristiti Yocto.

##### Yocto konfiguracija za Raspberry Pi 3:

Startati Docker Container spomenut u prethodnom poglavlju te slijediti sljedece upute.

Stvoriti inicijalnu struktura direktorija:

```
$ cd ~
$ mkdir yocto
$ cd yocto
```

Klonirati Poky koristeci Git:

```
$ git clone -b morty git://git.yoctoproject.org/poky.git poky-morty
```

Pozicionirati se u direktorij `poky`:

```
$ cd poky
```

Klonirati `meta-raspberrypi` koristeci Git:

```
$ git clone -b morty git://git.yoctoproject.org/meta-raspberrypi
```

Inicijalizirati build environment:

```
$ source oe-init-build-env
```

Podesiti `conf/bblayers.conf`:

```
$ vim conf/bblayers.conf
```

Dodati `meta-raspberrypi` u `BBLAYERS` varijablu:

```
BBLAYERS ?= " \
  /home/builder/yocto/poky/meta \
  /home/builder/yocto/poky/meta-yocto \
  /home/builder/yocot/poky/meta-yocto-bsp \
  /home/builder/yocto/poky/meta-raspberrypi \
  "
```

Podesiti `conf/local.conf`:

```
$ vim conf/local.conf
```

Promjeniti vrijednost `MACHINE` varijable u `raspberrypi3`:

```
MACHINE ??= "raspberrypi3"
```

Promjeniti vrijednost `EXTRA_IMAGE_FEATURES` varijable dodajuci `tools-debug`.

Na kraju datoteke dodati:

```
ENABLE_UART = "1"
```

Izraditi minimalni image GNU/Linux distribucije za Raspberry Pi 3:

```
$ bitbake rpi-basic-image
```

Izraditi SDK:

```
$ bitbake rpi-basic-image -c populate_sdk
```

Kada build uspijesno zavrsi, image za Raspberry Pi 3 se moze naci u sljedecem direktoriju:

```
tmp/deploy/images/raspberrypi3
```

SDK se moze naci u:

```
tmp/deploy/sdk
```

Spojiti microSD karticu u racunalo i saznati putanju do uredaja koji reprezentira microSD karticu. Izvrsiti sljedece naredbe da bi se image prebacio na microSD karticu. Zamjeni X u donjim naredbama sa specificnom konfiguracijom uredaja. Uredaj se moze doznati sa naredbama kao sto su `lsblk` ili `fdisk -l`:

```
$ sudo umount /dev/sdX
$ sudo dd if=tmp/deploy/images/raspberrypi3/rpi-basic-image-raspberrypi3.rpi-sdimg of=/dev/sdX
$ sync
$ sudo umount /dev/sdX
```

Spojiti TTL USB adapter na Raspberry Pi 3. Za detalje o spajanju vidjeti donju shemu i podatke za sam TTL USB adapter.
![Raspberry Pi 3 GPIO](https://www.element14.com/community/servlet/JiveServlet/previewBody/73950-102-10-339300/pi3_gpio.png)

Pokrenuti `ckermit` sa pripremljenim postavkama. Postavke ckermit serijske konzole se nalaze u direktoriju `/home/student/ckermit.conf`. `ckermit` ce omoguciti pristup konzoli ili terminalu preko serijske komunikacije.

Spojiti microSD karticu u Raspberry Pi 3 te ukljuciti ga na izvor napajanja sa prilozenim adapterom. Ukljucivanjem Raspberry Pi 3 na izvor napajanja ce rezultirati boot procesom. Ako je TTL USB adapter ispavno spojen na Raspberry Pi 3 te `ckermit` startan, boot poruke ce biti vidljive na terminalu. Nakon boot procesa, prikazat ce se login prompt. Koristeci korisnika root bez zaporke ulogirati se u sustav.

#### Debugging aplikacija pisanih u programskom jeziku C

U drugom djelu vjezbe ce studenti proci kroz nekoliko primjera aplikacija pisanih u programskom jeziku C koje u sebi imaju razne tipicne greske koje se dogadaju prilikom razvoja C/C++ aplikacija. Za potrebe debuganja aplikacija, studentima je unaprijed pripremljena VirtualBox VM masina. Na svakom racunalu je potrebno imati instaliran VirtualBox. Razlog tome je sto nam za razvoj aplikacije potreban GNU/Linux operacijski sustav koji sadrzi odredeni set alata potreban za razvoj i otkrivanje gresaka. Naglasak na ovom djelu vjezbe nisu znanja o C programskom jeziku, nego na okruzenju, skilovima i potrebnim alatima da bi se razvijala aplikacija za ugradene sustave. Cilj studentima ce biti da otkriju te greske te da njih i isprave.

Nakon cijele laboratorijske vjezbe, studenti ce dobiti uvid u sljedece tehnologije:

- GNU Toolchain
- Git
- CMake
- GDB
- Valgrind
- Vim
- Docker
- Yocto
