# Wrassling

A C++ wrestling game inspired by Brad Erkkila's Wrassling

[![Wrassling Demo Link](https://imgur.com/R8kn540.png)](https://www.youtube.com/watch?v=uobx0XPEGqs "Wrassling Demo")


## Description

This program visualizes the process of sorting a list filled with random numbers using the following algorithms:

* Bubble Sort
* Insertion Sort
* Heap Sort
* Merge Sort (In-place variation)
* Quick Sort
* Cycle Sort (this one is my favorite, even though it's the slowest)
* Cocktail Sort
* Shell Sort


The code for each of these algorithms can be found in the sorts.py file. I wrote each algorithm as a generator that yields whenever the algorithm reads or writes to the list. This allows the main pygame loop to refresh the screen after each list access and display where in the list the algorithm is currently making a change or reading data, (green for writes and red for reads).


The viewer.py file contains the code that models all data, and draws everything to the screen.


### Installing

* Download zip file and unzip into directory of your choice
* Open the viewer.py file and run

### Executing program

* Once you download all necessary files and run the viewer.py file, the main window should appear
* Increase the list size and tick speed to your liking
* Clicking any of the sort buttons will begin sorting
* During sorting, you can switch which algorithm is being used while maintaining the state of the list by clicking another sort button
* Once the list is completely sorted, there will be a small animation, after which, you can reshuffle the list by hitting the reset button
