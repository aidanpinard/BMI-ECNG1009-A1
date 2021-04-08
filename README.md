# BMI-ECNG1009-A1
Code I wrote for an assignment.

Scenario: Your team are tasked with developing a simple mobile application for a fitness center. According to the owner of the fitness center, they require your application to have the following major functionalities:
1. Registration
2. Instant BMI Calculation
3. Statistical Weight Tracker
4. Exit



Needed to:
- Write a function to return the BMI given the weight (kg), height (m) and gender (M/F) of the user where the BMI is calculated using the formula: 
  - BMI = weight/(√(height^3))∗ |1 − cos(weight / height)| for males OR
  - BMI = weight/(√(height^3))∗ |1 − sin(weight / height)| for females (note this isn't real BMI)
- Write a function that accepts 10 weight values (kg) from the user. Return the mean and standard deviation of the entered values as well as the percentage of the numbers entered that lie within two standard deviations on either side of the mean. The numbers are to be entered by a user on the console.
- And make menu with:
  1. The registration option prompts the user to enter the following data: Gender; Age; Height; Current Weight; Desired Weight.
  2. The Instant BMI Calculator calculates a BMI metric based on the gender, current weight and height.
  3. The Statistical Weight Tracker prompts the user to enter their recorded weights for each month for the past 10 months and computes appropriate statistics based on these recordings.
  -  Ensure that the user can navigate back to the main option screen once completed with each sub option. The program should exit only when the exit option is selected.
  
