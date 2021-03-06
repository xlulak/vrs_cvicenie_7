# Náplň cvičenia
- zoznámenie sa s perifériou DMA
- prenos dát s USART a DMA

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
- namiesto neustáleho vyvolávania funkcie na spracovanie prijatých dát sú využité 3 zdroje prerušenia - 2x od DMA, 1x od USART
- takto je funkcia na spracovanie dát vyvolaná len vtedy, ak je to potrebné
- prerušenia od DMA - HT(half transfer) a TC(transfer complete)
- prerušenie od USART - IDLE - ak sa zastaví komunikácia po zbernici, po uplinutí času potrebného na prenos jedného znaku sa vyvolá prerušenie

### Konfigurácia DMA
- prenos dát s DMA je nastavený na Rx aj Tx pričom Rx má rozdielnu konfiguráciu ako Tx
- smerovanie prenosu dát - periféria -> pamäť pri Rx, pamäť -> periféria pri Tx
- pri Rx sa ukladajú dáta do vyhradenej pamäti, do ktorej sa zapisuje "kruhovo" (circular mode) - ak sa naplní celé pamäťové miesto, ďalšie dáta sa začnú zapisovať na jeho začiatok a staré sa prepíšu
- pri Tx sa využije normálny mód (normal mode), to znamená, že keď sa dojde na koniec pamäťového miesta, prenos dáť sa ukončí

<p align="center">
    <img src="https://github.com/VRS-Predmet/vrs_cvicenie_7/blob/master/images/dma_config1.PNG" width="650">
</p>

- konfigurácia USART2 sa nelíši od konfigurácie z predchádzajúceho cvičenia
- V NVIC je potrebné povoliť prerušenia pre DMA(všetky používané kanály) aj USART2

- v ukážkovom kóde je navyše ku vygenerovanému kódu ešte doplňené povolenie konkrétnych prerušení pre DMA a USART (IDLE, HT, TC), priradenie pamäťového miesta pre príjem dát a samotné zapnutie DMA pre obsluhu USART2 Rx a Tx 
