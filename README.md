# Problema de los 100 prisioneros
Empirical cheking of solution for 100 prisoners problem.

## Problem descripcion
The director of a prison offers 100 death row prisoners, who are numbered from 1 to 100, a last chance. A room contains a cupboard with 100 drawers. The director randomly puts one prisoner's number in each closed drawer. The prisoners enter the room, one after another. Each prisoner may open and look into 50 drawers in any order. The drawers are closed again afterwards. If, during this search, every prisoner finds his number in one of the drawers, all prisoners are pardoned. If just one prisoner does not find his number, all prisoners die. Before the first prisoner enters the room, the prisoners may discuss strategy—but may not communicate once the first prisoner enters to look in the drawers. What is the prisoners' best strategy?

## Best solution
1. Each prisoner first opens the drawer with his own number.
2. If this drawer contains his number he is done and was successful.
3. Otherwise, the drawer contains the number of another prisoner and he next opens the drawer with this number.
4. The prisoner repeats steps 2 and 3 until he finds his own number or has opened 50 drawers.

How probability of surviving change when adding more prisoners.
![](http://miguelmerelo.es/100prisioneros/prob100prisioneros.png)
