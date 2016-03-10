package netdb.courses.softwarestudio.lab2;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import LotteryTicket.LotteryTicket;
import NumberGenerator.NumberGenerator;

public class LotteryLab {

	private static int[] winningNumbers = { 0, 0, 0, 0, 0, 0 };

	public static void main(String[] args) throws Exception {

		/**
		 * TODO Parse the arguments 'from', 'to', 'count'.
		 *
		 * - Your code here -
		 *
		 */
		int from = Integer.parseInt(args[0]);
		int to = Integer.parseInt(args[1]);
		int count = Integer.parseInt(args[2]);
		 System.out.println(from + "~" +to + " pick " + count + " numbers");
		 winningNumbers = NumberGenerator.generateWinningNumbers(from, to, count);
		/**
		 * TODO Use number generator's static method to generate the winning
		 * numbers and store it in the winningNumbers variable.
		 *
		 * - Your code here -
		 *
		 */

		// print the winning numbers
		printNumbers("Winning Numbers: ", winningNumbers);

		// create a scanner for input
		BufferedReader reader = new BufferedReader(new InputStreamReader(
				System.in));

		// print the user interaction message
		System.out
				.println("Please enter your ticket numbers: (ex:'1 2 3 4 5 6')");
		String inputString = "";
		
		// read a line and create a new ticket from input string
		while (!(inputString = reader.readLine()).equals("quit")) {
			printNumbers("Your ticket numbers: ", inputString);

			/**
			 * TODO The input numbers string is stored in the inputString. (You
			 * need to split the string first, and then convert the string
			 * number into integer)
			 *
			 * Create a lottery ticket with the number you picks and raffle it.
			 *
			 * - Your code here -
			 *
			 */
			int[] theNumbers = new int[10];
			String[] tokens = inputString.split(" ");
			if(tokens.length != count)
			{
				System.out.println("Stupid? Please input " +count +" numbers.");
			} else{
				int flag = 1;
				for(int ii=0; ii<count; ii++)
				{
					theNumbers[ii] = Integer.parseInt(tokens[ii]);
					if(theNumbers[ii] < from || theNumbers[ii] > to){
						System.out.println("Stupid? Please check the range.");
						flag = 2;
					}
				}
				for(int i = 0; i < count; i++){
					for(int k = 0; k < i; k++){
						if(theNumbers[i] == theNumbers[k]) {
							System.out.println("Stupid? Don't input same numbers.");
							flag = 0;
							break;
						}
					}
					if(flag == 0){
						break;
					}
				}
				if(flag == 1){
					LotteryTicket s = new LotteryTicket(theNumbers);
					s.raffle(winningNumbers);
				}
			}
			
			
			// prepare for the next loop
			Thread.sleep(1000);
			System.out
					.println("\nPlease enter your ticket numbers: (ex:'1 2 3 4 5 6')");
		}

		System.out.println("\nGoodbye~");

	}

	private static void printNumbers(String info, int[] numbers) {
		System.out.print(info + " ");
		for (Integer i : numbers)
			System.out.print(i + " ");
		System.out.println();
	}

	private static void printNumbers(String info, String numbers) {
		System.out.println(info + " " + numbers);
	}

}
