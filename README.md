# Strain guage

You will be designing and building a weight scale using a pre-built strain gauge bridge as shown in the link below:


Note that this package comes with a circuit board containing a custom load cell amplifier and 24 bit analog to digital converter (ADC). You will NOT be allowed to use this for your project. Instead, you will be reading the strain gauge output with the 10-bit ADC available on the Microchip PIC24FJ64GA002 microcontroller and the weight displayed on an appropriate LCD display. 

_**Detailed Specifications:**_

The system should display the weight of a test weight, in grams, to the nearest gram. The range should be 0-1000 grams. The system should have an auto zero ("tare") button to correct for any offset error. Note that a 10-bit ADC only has 1024 quantization levels so the system cannot correct large offset errors by digital offsets. Power supplies may be batteries, USB power, or wall power - it's your choice. The final system should function independently (not be tethered to a laptop other than possibly for power). More details will be provided in class.

_**The Boring Stuff:**_

1. Since the analog portion of the circuit will be connected to the analog to digital converter on your PIC board, putting the analog circuit in a box is not necessary, but you should plan on having it mounted in a stable fashion to facilitate testing and demonstration, If you do choose to put the circuit in a box, we suggest the  Bud 750-1015 box or equivalent, available from the ECE Depot, but other creative solutions are fine too including 3D printed boxes (there seems to be a competition every semester for who can make the cutest box); that's fine, but don't obsess too much about the box. The whole thing should be reasonable sized (6” on a side or less), if you feel you need to make a bigger board/box, please consult your TA first.

 

2. Components should be available from Digi-Key (they have the quickest delivery), Mouser Electronics (they are not quite as quick to ship as Digi-Key), or standard items from the ECE Depot. These parts will be ordered through the ECE Depot. A single IC containing the entire project is not permitted. If you wish to incorporate other parts from other suppliers you will be responsible for ordering and paying for them – we will not reimburse groups for these out of pocket expenses.

3. Instructions for Ordering Parts From the ECE Depot  Download Instructions for Ordering Parts From the ECE Depot(These instructions are from Fall 2023 but are still correct).

NOTE: not all parts listed in the supplier catalog are in stock, and ordering out of stock parts may result in substantial delays. Many parts are also surface mount – surface mount parts are often quite small and difficult to solder – if leaded parts (packages with leads like the ones you can plug into a proto-board) are available, they are usually the best choice. We have soldering facilities available in Anderson Labs, the ECE Depot (during the hours the Depot is open), and in the EXCEED lab.

Please designate ONE PERSON form your group to do all of the interfacing with the ECE Depot.

4. The total cost of all parts ordered through the ECE depot should not exceed $50. The circuit board, thermocouple wire, and thermocouple connectors do not need to be included in your budget.
