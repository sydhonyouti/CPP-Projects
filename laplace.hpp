#include <iostream>
#include <iomanip>
#include <math.h>
#include <mpi.h>
#include <vector>
#include "my_matrix.hpp"

namespace my
{
	using std::cin;
	using std::cout;
	using std::endl;
	using std::vector;

	struct Point
	{
		int row;
		int col;
	};
	struct HeatSource
	{
		Point UpperLeft;
		Point LowerRight;
		double temp;
	};

	struct laplace
	{
		// Basic parameters
		int NumProcess;
		int MyID;
		int NumRows;
		int NumCols;
		int RowsPerProc;

		// The "extended" values include the extra rows and columns
		int ExtendedR() { return NumRows + 2; }
		int ExtendedC() { return NumCols + 2; }
		int ExtendedRowsPerProcess() { return RowsPerProc + 2; }

		matrix<double> sheet;

		matrix<double> my_chunk;

		matrix<double> my_scratch;

		// Main process gets input from user
		void get_input(int*, int*, int*, std::vector <my::HeatSource>&);

		//Place Heat sources on matrix
		void fillSheetWithHeatSources(int, int, vector<HeatSource>);

		// Main process shares input with others
		void share_input();

		// Outer edges (row 0 and M + 1) only need to be shared once (they don't change)
		void share_outer_edges();

		// Inner edges need to be shared after every update
		void share_inner_edges();

		// Replace each cell with the average of its neigbhors
		bool advance();

		// Iterate until a fixed point is reached
		void solve(int);

		// Each process sends its results back to main process
		void collect_results(int pid, int numberOfProcesses, int numberOfRowsPerProcess, int nWithAir);

		// Main process outputs final results
		void print_results();

		//The master of the show
		void RunLaplace(int, int);
	};
}
