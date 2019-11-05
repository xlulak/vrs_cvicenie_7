# USART a DMA

- v ukážkovom programe sa na komunikáciu využíva periféria USART spolu s DMA (Direct Memory Access)
- predvedené sú dva spôsoby prenosu dát s DMA - polling, interrupts

- podľa nastavenia makra "POLLING" na "1" alebo "0" sa bude využívať jeden z uvedených spôsobov prenosu dát (makro sa nastavuje vo vlastnosťiach projektu, project->properties)

<p align="center">
    <img src="https://github.com/VRS-Predmet/vrs_cvicenie_7/blob/master/images/nastavenie_makra.PNG" width="750">
</p>

### Polling
- pri tomto spôsobe využívania DMA je v hlavnej slučke programu potrebné volať funkciu, ktorá zistí, či boli prijaté dáta a zabezpečí ich rýchle spracovanie
- funkcia musí byť vyvolávaná periodicky a dostatočne rýchlo, aby sa predišlo strate dát

### Interrupts
- 
