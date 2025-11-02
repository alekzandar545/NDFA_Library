bin folder for graphviz has to be added manually because the file is too large to be uploaded on moodle

//alright stuff is looking meh for now but its bound to get better

For the session i have to fix the issues with this project and show it to everybody
Key things that are a problem currently:

-unordered_set is not good for iteration so gotta pass on that
-unordered_set is also not a good key for a map-like datastructure
-lastly, hashing sets is awful because you have to go through each element and that is sloooow

1. unordered_set is not a good choice for my transitions container
--2. unordered_set is also not good for storing the alphabet(can use bitset for that way more effectively)
--6. the stack doesn't resize on its own
--7. differenciate between semantic exceptions and input format exceptions in the deserialize/serialize(not validating the input)
--8. think about the oop stuff in the beginning. Do we even need all those constructors?
9. in regex funcion dont copy objects.
10. can use pointers in the stack and queues, as not to create copy and destroy objects every time
--11. adjacency matrix for automata transitions
--12. OOP BIG 6 IS REDUNDANT SINCE IM NOT USING DYNAMIC MEMORY ALLOCATION!