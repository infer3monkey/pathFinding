# Summary

This is an algorithm that allows you to find a valid path or lack there of when given a word and a 2d array of characters

a valid path means that the first letter must be adjacent to the second and the second must be adjacent to the third and so on

there are 3 sample 2d arrays of characters which are named puzzle1.txt, puzzle2.txt, and puzzle3.txt

if you wanted to run this you would need to pass in one of those files or one of your own creation when running the file so if your executable file was named app then you could run this
`./app puzzle1.txt`

# Algorithm

The algorithm that I created to solve this problem is a recursive function that when you find the correct letter you branch off. 

For example if the word was hello once I found the first h I would then start looking for e's but if there were no e's adjacent to that h then my function would go and find a new h. If no other h's exist then there wouldn't be a solution. However if a solution exists the alogirthm will return the first path that works and stop there
