# *POO_Proiect_2020*
Project made for University with my teammates to simulate a console application database that stores data in files.

We handled to implement basic commands from SQL like creating a table and it's structure, deleting the tables, displaying the table's structures, but unfortunately the time was short and we didn't manage to finish all the features that we wanted to implement.

Unfortunately, we had to use files for storing the data and other primitive work methods like char*, not using libraries etc, because that was the main point of the project.
# Features
## Reading commands from console
One of the hardest tasks to achieve was reading and processing commands from the user in the console application. 
Every command is split into words and if a word or a sign is wrong the program will throw a specific error.
## Database Objects
When the application starts, the program will create a database for the user where all his tables/data will be stored in computer's random-access memory.
When the program is turned off, everything will be lost. This feature is made for the purpose to structure the tables, lines and columns.
Also in the database objects most of the operations are performed: creating, displaying and deleting tables.
## Reading commands from files
This feature is very useful because the user can throw a script in a file and the program will get every command in the file. 
## Save data in files
When the "commit" command is triggered the program will save all the tables structure into files.
## Fetch data from files
One of our goals was to fetch data that is stored on files and everytime the user starts the program, the database object will be actualized.
This feature is very important, because once the user closes the application the data won't be lost.
## Cases
The project involves an algorithm that use cases in order to trigger functions in the program to do specific tasks from user's commands.
