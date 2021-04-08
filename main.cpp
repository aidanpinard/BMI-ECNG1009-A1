#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <cstring>
// Note: XML documentation is used
// copy this code into visual studio and 
// hover over the functions to see the results


/// =======================================================
///                         Structs
/// =======================================================

/// <summary>
/// This represents a user of the application. The registration menu sets 
/// the values for the user. This identifies the user as registered and 
/// allows the information to be used in the BMI calculator.
/// </summary>
struct userInfo {
  // Represents if the user is registered.
  bool registered = 0;
  // The registration data.
  bool isMale = 0;
  int age = 0;
  float height = 0;
  float currentWeight = 0;
  float desiredWeight = 0;

  // Creates a registered user using the user's data
  userInfo(bool iM, int a, float h, float cw, float dw) {
    registered = 1;
    isMale = iM;
    age = a;
    height = h;
    currentWeight = cw;
    desiredWeight = dw;
  }

  // Creates a default unregistered user.
  userInfo() {
    registered = 0;
    isMale = 0;
    age = 0;
    height = 0;
    currentWeight = 0;
    desiredWeight = 0;
  }
  
};

/// =======================================================
///                    Custom Functions
/// =======================================================


/// <summary> 
/// Stop the program execution until the user presses a key. 
/// </summary>
/// <param name='comment'>:  
/// An optional comment to display. Note: Windows command prompts 
/// may not display this comment. 
/// </param>
void pause(std::string comment) {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  /// pause has slightly different behaviour depending on what executes it
  /// but is generally press enter to continue.
  system(("pause " + comment).c_str());
#else
  /// Bash execute read
  /// -n1 : read only 1 key
  /// -r : read \ as a single key instead of as part of an escape sequence
  /// -s : do not show the entered key
  /// -p : take the next word as a prompt
  system(("bash -c 'read -n1 -r -s -p \"" + comment + "\"'").c_str());
#endif
}

/// <summary>
/// Clears the console screen of text.
/// </summary>
void clearScreen() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  /// Windows
  system("cls");
#else
  /// Most other cmd 
  system("clear");
#endif
}

/// <summary>
/// Calculate the BMI for a man or woman using their mass in 
/// kg and height in m.
/// </summary>
/// <param name='massKg'> :
/// A double representing the mass in kilograms of the person.
/// </param>
/// <param name='heightM'> :
/// A double representing the height in meters of the person.
/// </param>
/// <param name='isMale'> :
/// A bool representing if the person is male or female. 
/// (true for male | false for female).
/// </param>
/// <returns> The calculated BMI. </returns>
double calculateBmi(double massKg, double heightM, bool isMale) {
  return ((massKg / std::sqrt(std::pow(heightM, 3))) *
    (std::abs(1 -
      (isMale
        ? std::cos(massKg / heightM)
        : std::sin(massKg / heightM)))));
}

/// <summary>
/// Calculates the mean value from an array of numbers.
/// </summary>
/// <param name="values">: The array of values to find the mean of. </param>
/// <returns> The mean. </returns>
template<int length>
double calculateMean(const double(&values)[length]) {
  double mean = 0;
  // applying incremental mean formula
  // m_n = m_{n-1} + \frac{ a_n - m_{n-1} }{ n }
  for (int i = 0; i < length; i++) {
    mean += ((values[i]-mean)/(i+1));
  }
  return mean;
}

/// <summary>
/// Calculates the standard deviation for an array of values given.
/// </summary>
/// <param name="values">: 
/// The values to calculate the standard deviation with.
/// </param>
/// <param name="mean">: 
/// The mean of the values provided (to avoid recalculation). 
/// </param>
/// <returns> The standard deviation. </returns>
template<int length>
double calculateStandardDeviation(const double(&values)[length], double mean) {
  double temp = 0;

  // Sum the square of mean differences and return the square root of 
  // the mean differences divided by length

  for (double value : values) {
    temp += std::pow((value - mean), 2);
  }
  return std::sqrt(temp / 10);
}

/// <summary>
/// Calculates the percent of values within 2 standard deviations of the mean.
/// </summary>
/// <param name="values">: 
/// The values to compare to the mean. 
/// </param>
/// <param name="mean">: 
/// The mean of the values given (to avoid recalculation). 
/// </param>
/// <param name="standardDeviation">: 
/// The standard deviation of the values given (to avoid recalculation). 
/// </param>
/// <returns> 
/// A float values representing the percent of values within 2 standard
/// deviations of the mean. 
/// </returns>
template<int length>
float percentWithinTwoStdDev(const double(&values)[length],
  double mean, double standardDeviation) {
  // Increment withinTwoStdDev for each value within 2 
  // standard deviations of the mean.
  float withinTwoStdDev = 0;
  for (double value : values) {
    if (std::abs((value - mean)) <= (2 * standardDeviation)) {
      withinTwoStdDev++;
    }
  }
  // Divide the values within two std dev by the total number 
  // of values and return the percent
  return (withinTwoStdDev / length) * 100;
}

/// <summary>
/// Ask user their gender and return whether they are male or not
/// </summary>
/// <returns>
/// A bool representing their sex.
/// </returns>
bool getIfUserIsMale() {
  std::string sex = "";

  // while input is not valid, stay in the loop
  while (1) {
    std::cout << "Are you a male or female? (M or F): ";

    // Grab user input
    std::cin >> sex;
    // convert to lowercase
    std::transform(sex.begin(), sex.end(), sex.begin(), ::tolower);
    // if male return true
    if (sex == "m" || sex == "male") {
      std::cout << "\n";
      return 1;
    }
    // if female return false
    else if (sex == "f" || sex == "female") {
      std::cout << "\n";
      return 0;
    }
    // else try again
    else {
      std::cout << "Please enter M or F.\n\n";
    }
  }
}

/// <summary>
/// Ask user their age.
/// </summary>
/// <returns> An integer representing their age</returns>
int getAge() {
  int age = 0;

  while (1) {
    std::cout << "Please enter your age in years: ";
    std::cin >> age;

    // Validating user input
    if (!std::cin.good() 
      || age <= 0 
      || (std::cin.peek() > -1
      && std::cin.peek() != 10
      && std::cin.peek() != 13)) {
      std::cout << "Invalid input detected. Please enter a valid value. \n\n";
      std::cin.clear();
      std::cin.ignore();
    }
    else {
      // When valid data is detected add a newline, return the age and
      // exit the loop
      std::cout << "\n";
      return age;
    }
  }
}


/// <summary>
/// Asks user their height in meters.
/// </summary>
/// <returns>
/// A float representing their height.
/// </returns>
float getHeight() {
  float height = 0;

  while (1) {
    std::cout << "Please enter your height in meters: ";
    std::cin >> height;

    // Validating user input
    if (!std::cin.good() || height <= 0) {
      std::cout << "Invalid input detected. Please enter a valid value. \n\n";
      std::cin.clear();
      std::cin.ignore();
    }
    else {
      // When valid data is detected add a newline, return the height and 
      // exit the loop
      std::cout << "\n";
      return height;
    }
  }
}

/// <summary>
/// Ask user their weight.
/// </summary>
/// <param name="weightType">:
/// A descriptor of the weight being asked for.
/// </param>
/// <returns></returns>
float getWeight(std::string weightType) {
  float weight = 0;

  while (1) {
    std::cout << "Please enter your "
      << weightType
      << " weight in kilograms: ";
    std::cin >> weight;

    /// Validating user input
    if (!std::cin.good() || weight <= 0) {
      std::cout << "Invalid input detected. Please enter a valid value. \n\n";
      std::cin.clear();
      std::cin.ignore();
    }
    else {
      // When valid data is detected add a newline, return the height and 
      // exit the loop
      std::cout << "\n";
      return weight;
    }
  }
}


/// =======================================================
///                        Menus
/// =======================================================


/// <summary>
/// Display the registration menu and accept user input
/// </summary>
/// <returns>
/// A registered user with the information accepted.
/// </returns>
userInfo registrationMenu() {
  std::cout << "Welcome to the Fitness Center Application.\n"
    << "==========================================\n"
    << "                Registration              \n\n";

  // Get inital values.
  bool isMale = getIfUserIsMale();
  int age = getAge();
  float height = getHeight();
  float currentWeight = getWeight("current");
  float desiredWeight = getWeight("desired");

  // while input is not valid, stay in the loop
  while (1) {
    clearScreen();
    // Show the inital values and confirm.
    std::cout << "Welcome to the Fitness Center Application.\n"
      << "==========================================\n"
      << "           Finalize Registration          \n"
      << "\n"
      << "Do you wish to change any of the following settings?\n\n"
      << "1. Gender: " << ((isMale) ? ("Male") : ("Female")) << "\n"
      << "2. Age: " << age << "y/o \n"
      << "3. Height: " << std::fixed << std::setprecision(2)
      << height << "m\n"
      << "4. Current Weight: " << std::fixed << std::setprecision(2)
      << currentWeight << "kg \n"
      << "5. Desired Weight: " << std::fixed << std::setprecision(2)
      << desiredWeight << "kg \n"
      << "6. Save and return to the Main Menu."
      << "\n> ";

    int choice = 0;
    std::cin >> choice;
    // Check for invalid data
    if (!std::cin.good()
      || choice < 1
      || choice > 6
      || (std::cin.peek() > -1
        && std::cin.peek() != 10
        && std::cin.peek() != 13)) {
      std::cout << ((!std::cin.good())
        ? ("Invalid input detected. "
          "Please enter a number corresponding to the menu's choices.")
        : "Please enter a valid choice from the menu.") << "\n\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      pause("Press any key to continue...");
    }
    else {
      clearScreen();
      // If they want to edit show the option to edit and return to the main 
      // editor or if they choose the exit option then exit with the data.
      std::cout << "Welcome to the Fitness Center Application.\n"
        << "==========================================\n"
        << "         Editing Registration Data        \n\n";
      switch (choice) {
      case 1:
        isMale = getIfUserIsMale();
        break;
      case 2:
        age = getAge();
        break;
      case 3:
        height = getHeight();
        break;
      case 4:
        currentWeight = getWeight("current");
        break;
      case 5:
        desiredWeight = getWeight("desired");
        break;
      case 6:
        // return a registered user
        return userInfo(isMale, age, height, currentWeight, desiredWeight);
      default:
        // If an unexpected error occurs, print an error message, and restart. 
        std::cout << "An error occurred. "
          "Please report this error to the staff.\n";
        pause("Press any key to continue...");
        break;
      }
    }
  }
}

/// <summary>
/// Display the BMI menu and ask for user's height, weight and sex
/// then call the calculate BMI function.
/// </summary>
/// <param name="user">:
/// The user whose information will be user to calculate the BMI.
/// </param>
void bmiMenu(userInfo user) {
  std::cout << "Welcome to the Fitness Center Application.\n"
    << "==========================================\n"
    << "          Instant BMI Calculator          \n\n";
  // If they haven't registered then leave.
  if (!user.registered) {
    std::cout << "You have not registered yet. Please register before"
      " attempting to get your BMI.\n\n";
  }
  else {
    // Get their BMI and print it.
    float bmi = calculateBmi(user.currentWeight, user.height, user.isMale);
    std::cout << "Your BMI is " << std::fixed << std::setprecision(2)
      << bmi << ".\n";
  }

  pause("Press any key to continue...");
}

/// <summary>
/// Ask for 10 weights and print the mean weight and the percent of weights
/// within 2 standard deviations of the mean.
/// </summary>
void statisticalWeightTrackerMenu() {
  std::cout << "Welcome to the Fitness Center Application.\n"
    << "==========================================\n"
    << "         Statistical Weight Tracker       \n\n";

  /// Storing all the weights entered by the user
  double weights[10] = {};

  for (int i = 0; i < 10; i++) {
    /// Getting the user input
    bool validInput = 0;
    double temp = 0;

    while (!validInput) {
      std::cout << "Please enter weight no. " << i + 1 << ": ";
      std::cin >> temp;

      /// Validating user input
      if (!std::cin.good() || temp <= 0) {
        std::cout << "Invalid input detected. "
          "Please enter a valid value. \n\n";
        std::cin.clear();
        std::cin.ignore();
      }
      else {
        // When valid data is detected add a newline, save the 
        // data and exit the loop
        std::cout << "\n";
        weights[i] = temp;
        validInput = 1;
      }
    }
  }

  // calculate the values
  double mean = calculateMean(weights);
  double standardDeviation = calculateStandardDeviation(weights, mean);
  float percentWeightsWithinTwoStandardDeviations =
    percentWithinTwoStdDev(weights, mean, standardDeviation);

  // output the values
  std::cout << "The mean weight is " << std::fixed
    << std::setprecision(2) << mean << "kg.\n";
  std::cout << std::fixed << std::setprecision(2)
    << percentWeightsWithinTwoStandardDeviations
    << "% of the values are within 2 standard deviations of the the mean.\n";
  pause("Press any key to continue...");
}

void mainMenu(userInfo user) {
  // Initialise the user choice and validation variable

  int choice = 0;
  bool validChoice = 0;

  // while input is not valid, stay in the loop
  while (!validChoice) {
    // Clear screen and output the menu.
    clearScreen();
    std::cout << "Welcome to the Fitness Center Application.\n"
      << "==========================================\n"
      << "                 Main Menu                \n"
      << "    (Enter a number to select a choice)   \n"
      << "\n"
      << "1. Registration \n"
      << "2. Instant BMI calculation \n"
      << "3. Statistical Weight Tracker \n"
      << "4. Exit \n"
      << "\n> ";

    // Grab user input
    std::cin >> choice;

    // If user input is invalid (a letter, a non-integer or a number that 
    // does not correspond to a menu option) inform the user and clear the 
    // input stream.
    // Else exit the loop.
    if (!std::cin.good()
      || choice < 1
      || choice > 6
      || (std::cin.peek() > -1
        && std::cin.peek() != 10
        && std::cin.peek() != 13)) {
      std::cout << ((!std::cin.good())
        ? ("Invalid input detected. "
          "Please enter a number corresponding to the menu's choices.")
        : "Please enter a valid choice from the menu.") << "\n\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      pause("Press any key to continue...");
    }
    else {
      validChoice = 1;
    }
  }

  clearScreen();

  // Enter a menu or exit depending on the choice that was made. 
  switch (choice) {
  case 1:
    // Enter the registration menu and get the registered user
    user = registrationMenu();
    break;
  case 2:
    // Enter the BMI menu using the current user (registered or unregistered)
    bmiMenu(user);
    break;
  case 3:
    // Enter the Statistical weight tracker.
    statisticalWeightTrackerMenu();
    break;
  case 4:
    // Print goodbye and exit.
    std::cout << "Thank you for using the Fitness Center Application. "
      "Have a nice day.\n";
    return;
  default:
    // If an unexpected error occurs, print an error message, and restart. 
    std::cout << "An error occurred. Please report this error to the staff.\n";
    pause("Press any key to continue...");
    break;
  }

  // re-enter the main menu.
  mainMenu(user);
}

int main() {
  // Enter the main menu with a empty user.
  mainMenu(userInfo());
  return 0;
}