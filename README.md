# Programming with Sockets

## Project Description

Ky projekt paraqet një implementim praktik të komunikimit klient-server duke përdorur protokollin **UDP**. Ai është zhvilluar në gjuhën **C++** në mjedisin **Windows** dhe demonstron mënyrën se si një server dhe disa klientë mund të komunikojnë në rrjet për të kryer operacione të caktuara.

Serveri ruan skedarë të ndryshëm, përfshirë një **skedar tekstual** dhe një **batch file**, ndërsa klientët mund të ndërveprojnë me serverin duke dërguar kërkesa të ndryshme. Sistemi është ndërtuar mbi një model me role, ku ekzistojnë dy role kryesore: **admin** dhe **klient**. Admini ka privilegje shtesë, si shkrimi në skedarët e serverit dhe ekzekutimi i komandave të caktuara, ndërsa klientët e zakonshëm kanë qasje më të kufizuar.

Funksionalitetet kryesore të projektit përfshijnë:
- leximin e një skedari të ruajtur në server,
- shkrimin në atë skedar me autorizim të adminit,
- marrjen dhe ekzekutimin e një **batch file** nga serveri në kompjuterin e klientit.

Ky projekt është testuar me sukses në një rrjet real lokal duke përdorur të paktën **katër pajisje të ndryshme**, sipas kërkesave të detyrës. Një pajisje ka funksionuar si server, ndërsa pajisjet tjera janë lidhur si klientë në të njëjtin rrjet përmes **Wi-Fi** ose **hotspot-it**. Gjatë testimit është verifikuar dërgimi dhe pranimi korrekt i mesazheve ndërmjet pajisjeve, si dhe funksionimi stabil i komunikimit përmes UDP-së.

## Features

- **Role-Based Access Control**  
  Sistemi përkrah dy role: **admin** dhe **klient**.

- **Admin Login me fjalëkalim**  
  Admini ka të drejtë për lexim, shkrim dhe ekzekutim.

- **Hidden Password Input**  
  Fjalëkalimi nuk shfaqet gjatë hyrjes për siguri.

- **Read Command**  
  Klienti mund të lexojë përmbajtjen e skedarit në server.

- **Write Command**  
  Admini mund të shtojë tekst në skedar.

- **Execute Command**  
  Klienti mund të marrë dhe ekzekutojë një batch file nga serveri.

- **File Handling**  
  Serveri menaxhon skedarët për testim dhe demonstrim.

- **Client-Side Execution**  
  Batch file ekzekutohet në kompjuterin e klientit.

## Configuration Requirements

- Windows OS  
- C++ Compiler  
- Winsock2 library  
- conio.h për fshehjen e password-it  

## Expected Results

- Komunikim korrekt klient-server përmes UDP  
- Admin login i sigurt  
- Lexim dhe shkrim në skedar nga serveri  
- Ekzekutim i batch file në klient  
- Funksionim stabil në rrjet lokal  

## Përfundim

Ky projekt paraqet një zgjidhje funksionale dhe të qartë për komunikimin ndërmjet serverit dhe klientëve në rrjet. Përmes organizimit të roleve dhe funksioneve të ndryshme, sistemi arrin të kryejë detyrat e kërkuara në mënyrë të saktë dhe efikase.

