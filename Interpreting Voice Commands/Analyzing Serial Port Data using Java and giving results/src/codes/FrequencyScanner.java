package codes;

import java.io.*;
import java.util.Scanner;

public class FrequencyScanner {

	// taking data from the Arduino and analyzing it to find the voice input

	public static boolean Frequency = false, Duration = false; // booleans to check which area of the file (stored in their respective arrays) is being checked
	public static int TotalNumberOfItems = 500; // dictating the size of the array
	public static int DurationDatabase[] = new int[TotalNumberOfItems]; // database to store duration-data
	public static int FrequencyDataBase[] = new int[TotalNumberOfItems]; // database to store frequency-data
	public static int counter = 0, SecondaryCounter = 0; // keeping track of the array instance
	public static int ClosestChoice = 0; // keeping track of the closest choice
	public static boolean Found = false; // boolean to track instance in the array

	public static void main(String[] args) throws FileNotFoundException {
		TakeInputFromFile();

		// Taking Input from Current Source
		Scanner Entrance = new Scanner(System.in);
		int HighestFrequency = Entrance.nextInt();
		int Duration = Entrance.nextInt();
		
		// go through the array and compare
		for (int x = 0; x < 1; x++)
			if (HighestFrequency == FrequencyDataBase[x])
				ClosestChoice = x;
		if ((DurationDatabase[ClosestChoice] + 5) == Duration) { // verifying if it is the right choice
			Found = true;
		}

		if (!Found) {
			for (int x = 0; x < 1; x++)
				if (Duration == DurationDatabase[x])
					ClosestChoice = x;
		}
		System.out.println(FindLabel());
		/// Set up a system to compare variable int's to inputs from file to find the
		/// closest sound that matches
		// Ones closest sound is found, go through another list to find which sound it
		/// is from
	}

	public static void TakeInputFromFile() throws FileNotFoundException {
		File infile = new File("FrequencyandDuration.txt"); // dictating the file
		Scanner Input = new Scanner(infile); // Initializing the means to decipher and read the file

		while (Input.hasNext()) { // storing all the items in a database
			String Data = Input.next();
			if (Data.equals("Frequency")) {
				// System.out.println("Hello");
				Frequency = true;
				Duration = false;
				Data = Input.next();
			}

			else if (Data.equals("Duration")) {
				Frequency = false;
				Duration = true;
				Data = Input.next();
			}

			if (Frequency) {
				FrequencyDataBase[SecondaryCounter] = Integer.parseInt(Data);
				SecondaryCounter++;
			}

			else if (Duration) { // if the item is measured by a Duration price system
				DurationDatabase[counter] = Integer.parseInt(Data);
				counter++;
			}
		}
		Input.close(); // closing the input reader
	}

	public static String FindLabel() throws FileNotFoundException {
		File infile = new File("DataLabels.txt"); // dictating the file
		Scanner Input = new Scanner(infile); // Initializing the means to decipher and read the file
		String Label = null;
		int Counter = 0;
		while (Input.hasNext()) { // storing all the items in a database
			String Data = Input.next();
			Counter = Counter++;
			if (Counter == ClosestChoice)
				Label = Data;
		}
		Input.close(); // closing the input reader
		return Label;
	}
}
