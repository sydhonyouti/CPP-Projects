#include "laplace.hpp"

/* The user inputs the information or data for the main process which will then go to share the input next
Following on the shared information (MAIN ONLY) the function Outer edges which starts from row 0 to Mod + 1
WIll be shared once. This value will never change. The inner edges need to be shared after every update
Along with the advance function that will replace each cell with the average of its neighbors
Here will will iterate until a fixed point is reached. Then it will send the results back to main
Out put the final results and then fill the heat source map. Once filled and given the order to run Laplace
*/

namespace my {

	void laplace::init(int DataArg1, char* DataArg2[])
	{
		MPI_Init(&DataArg1, &DataArg2);
		MPI_Comm_rank(MPI_COMM_WORLD, &id);
		MPI_Comm_size(MPI_COMM_WORLD, &NumProcess);
	}

	void laplace::get_input(int* Mod1, int* NumArg, int* HeatArg, vector <HeatSource>& HeatSources)
	{
		cin >> *Mod1;
		cin >> *NumArg;
		cin >> *HeatArg;
		int i;
		for (i = 0; i < *HeatArg; i++)
		{
			HeatSource t;
			cin >> t.UpperLeft.row;
			cin >> t.UpperLeft.col;
			cin >> t.LowerRight.row;
			cin >> t.LowerRight.col;
			cin >> t.temp;
			HeatSources.push_back(t);
		}
	}

	void laplace::share_input()
	{
		MPI_Bcast(&NumRows, 1, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Bcast(&NumCols, 1, MPI_INT, 0, MPI_COMM_WORLD);
	}

	// Outer edges(BROADCAST AT A LATER POINT)
	void laplace::share_outer_edges()
	{
		if (id == 0)
		{
			for (int proc = 1; proc < NumProcess - 1; proc++)
			{
				for (int i = 0; i < ExtendedRowsPerProcess(); i++)
				{
					MPI_Send(&sheet[(proc * RowsPerProc) + i][0], ExtendedC(), MPI_DOUBLE, proc, 0, MPI_COMM_WORLD);
				}
			}
			for (int i = 0; i < ExtendedRowsPerProcess(); i++)
			{
				for (int j = 0; j < ExtendedC() - 1; j++)
				{
					my_chunk[i][j] = sheet[i][j];
				}
			}
		}
		else
		{
			for (int i = 0; i < ExtendedRowsPerProcess(); i++)
			{
				MPI_Recv(&my_chunk[i][0], ExtendedC(), MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			}
		}
	}

	// Inner edges
	void laplace::share_inner_edges()
	{
		double* MyLastRow = &my_chunk[RowsPerProc - 2][0];
		double* MyFirstRow = &my_chunk[1][0];
		double* SheetFirstRow = &my_chunk[0][0];
		double* SheetLastRow = &my_chunk[RowsPerProc - 1][0];

		if (id == 0)
		{
			MPI_Send(MyLastRow, ExtendedC(), MPI_DOUBLE, id + 1, 0, MPI_COMM_WORLD);
			MPI_Recv(SheetLastRow, ExtendedC(), MPI_DOUBLE, id + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
		else if (id == NumProcess - 1)
		{
			MPI_Send(MyFirstRow, ExtendedC(), MPI_DOUBLE, id - 1, 0, MPI_COMM_WORLD);
			MPI_Recv(SheetFirstRow, ExtendedC(), MPI_DOUBLE, id - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
		else
		{
			MPI_Send(MyLastRow, ExtendedC(), MPI_DOUBLE, id + 1, 0, MPI_COMM_WORLD);
			MPI_Recv(SheetLastRow, ExtendedC(), MPI_DOUBLE, id + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			MPI_Send(MyFirstRow, ExtendedC(), MPI_DOUBLE, id - 1, 0, MPI_COMM_WORLD);
			MPI_Recv(SheetFirstRow, ExtendedC(), MPI_DOUBLE, id - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
	}

	// Advance function
	bool laplace::advance()
	{
		my_scratch = my_chunk;
		int row;
		int col;
		bool result = false;
		for (row = 1; row < RowsPerProc + 1; row++)
		{
			int colWithAir = ExtendedC();
			for (col = 1; col < colWithAir - 1; col++) {
				double rowAbove = my_scratch[row + 1][col];
				double rowBelow = my_scratch[row - 1][col];
				double columnRight = my_scratch[row][col + 1];
				double columnLeft = my_scratch[row][col - 1];
				double currentValue = my_scratch[row][col];
				double sumOfAdjacent = (rowAbove + rowBelow + columnRight + columnLeft);
				double newValue = sumOfAdjacent / 4;
				double currentAndNewDifference = fabs(currentValue - newValue);

				my_scratch[row][col] = newValue;
				if (currentAndNewDifference > 0.001)
				{
					result = true;
				}
			}
		}
		std::swap(my_chunk, my_scratch);
		return result;
	}

	//Solve function fo the iteration
	void laplace::solve(int id)
	{
		cout << "solve!" << endl;
		bool Continue = true;
		bool Changed;
		while (Continue)
		{
			Changed = false;
			Continue = false;
			share_inner_edges();
			Changed = advance();
			MPI_Allreduce(&Changed, &Continue, 1, MPI_LOGICAL, MPI_LOR, MPI_COMM_WORLD);
		}
	}

	//output final results
	void laplace::print_results(int pid = 0)
	{
		for (int i = 0; i < NumProcess; ++i) {
			if (MyID == i) {
				for (int c = 0; c < ExtendedR(); c++) {
					for (int b = 0; b < ExtendedC(); b++) {
						cout << std::setprecision(3) << std::fixed << std::setw(6) << my_chunk[c][b];
					}
					cout << endl;
				}
			}
			MPI_Barrier(MPI_COMM_WORLD);
		}
	}


	//fills sheet with heat sources
	void laplace::fillSheetWithHeatSources(int Mod2, int NumSource, vector<HeatSource> Heat)
	{
		int i;
		for (i = 0; i < Heat.size(); i++)
		{
			HeatSource heatSource = Heat[i];
			int Row, Column;
			for (Row = heatSource.UpperLeft.row; Row <= heatSource.LowerRight.row; Row++)
			{
				for (Column = heatSource.UpperLeft.col; Column <= heatSource.LowerRight.col; Column++)
				{
					sheet[Row][Column] = heatSource.temp;
				}
			}
		}
	}

	//Run Laplace
	void laplace::RunLaplace(int id, int Proc)
	{
		vector<HeatSource> heatsources;
		if (id == 0)
		{
			get_input(&NumRows, &NumCols, &NumProcess, heatsources);
			sheet.resize(NumRows + 2, NumCols + 2);

			MPI_Bcast(&NumRows, 1, MPI_INT, 0, MPI_COMM_WORLD);
			MPI_Bcast(&NumCols, 1, MPI_INT, 0, MPI_COMM_WORLD);
			fillSheetWithHeatSources(NumRows, NumCols, heatsources);
		}
		else
		{
			MPI_Bcast(&NumRows, 1, MPI_INT, 0, MPI_COMM_WORLD);
			MPI_Bcast(&NumCols, 1, MPI_INT, 0, MPI_COMM_WORLD);
			my_chunk.resize(ExtendedR(), ExtendedC());
		}
		RowsPerProc = NumRows / NumProcess;
		my_chunk.resize(ExtendedRowsPerProcess(), ExtendedC());
		share_outer_edges();
		//This will be the end of the program
		solve();
		print_results();
	}
}