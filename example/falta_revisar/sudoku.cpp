// $Id$

/* 
   COMIENZO DE DESCRIPCION 

    __USE_WIKI__
    [Tomado en recuperatorio ].
    keywords: set

    FIN DE DESCRIPCION */

// -----------------------------------------------------------------
#include <cstdio>
#include <cassert>
#include <vector>
#include <list>
#include <set>
using namespace std ;

void docver_print();

// This class keeps a Sudoku board
class board_t {
private:
  // For each cell we store the `entry' (i.e. the
  // value in the cell), If the entry is `0' it means
  // that the value is unset. Also we store the
  // set of admissible values in the cell.
  class cell_t {
    friend class board_t;
    int entry;
    set<int> admissible;
  };
  // `size' is the length of each
  // `sizer' is the length of the row
  // `sizeb' is the total number of cells in the board
  // In the standard sudoku we have
  // size=3, sizer=9, sizeb=81
  int size,sizer,sizeb;
  // Linear vector storing a `cell_t' structure 
  vector<cell_t> w;
  // Stores a stack with the pending states
  // when `guessing'
  list<vector<cell_t> > state_stack;

  // Pick a random element from a set
  int rand_pick(set<int> &s) {
    int n = s.size();
    assert(n>0);
    int j= rand() % n;
    set<int>::iterator q = s.begin();
    for (int k=0; k<j; k++) q++;
    return *q;
  }

public:
  typedef vector<cell_t> state_t;
  // Stores all solutions for the initial board
  list<state_t > solutions;

  // Controls  verbosity
  int verbose;
  // `solve()' doesn't return all solutions. Only check if
  // initial board has 0, 1 or multiple solutions.
  int compute_all_solutions;

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  // Default constructor, initializes an empty board
  board_t(int s=3) 
    : size(s), sizer(size*size), 
      sizeb(sizer*sizer), 
      verbose(0),
      compute_all_solutions(1) { 
    set<int> empty;
    for (int j=1; j<=sizer; j++) 
      empty.insert(j);
    
    w.resize(sizeb);
    for (int j=0; j<sizeb; j++) {
      w[j].entry = 0;
      w[j].admissible = empty;
    }
  };

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  // Return entry at position (j,k)
  const int &val(int j,int k) { return w[size*j+k].entry; }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  // Set the (j,k) entry to `entry'.
  // Also revise the cells in the corresponding square, row
  // and columns, in order to eliminate `entry' from the
  // admissible values for those cells.
  bool set_entry(int j, int k, int entry) {
    assert(j>=0 && j<sizer);
    assert(k>=0 && k<sizer);

    set<int> &s = w[sizer*j+k].admissible;
    if (s.erase(entry)==0) return false;

    w[sizer*j+k].entry = entry;
    
    // Revise square
    int 
      j2b=(j/size)*size,
      k2b=(k/size)*size;
    for (int j2=j2b; j2<j2b+size; j2++) 
      for (int k2=k2b; k2<k2b+size; k2++) 
        w[j2*sizer+k2].admissible.erase(entry);

    // Revise row
    for (int k2=0; k2<sizer; k2++) 
      w[j*sizer+k2].admissible.erase(entry);

    // Revise column
    for (int j2=0; j2<sizer; j2++) 
      w[j2*sizer+k].admissible.erase(entry);

    // Set the admissible set to `{entry}'
    w[sizer*j+k].admissible.clear();
    w[sizer*j+k].admissible.insert(entry);

    return true;
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  // Initialize from a vector of entry values.
  // A null entry means that entry is not set.
  void init(const int *v) {
    for (int j=0; j<sizer; j++) 
      for (int k=0; k<sizer; k++) {
        int entry = v[j*sizer+k];
        if (entry>0) set_entry(j,k,entry);
      }
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  // Print the board
  void print(int admi=0) {
    for (int js=0; js<size; js++) {
      if (js>0) {
        for (int l=0; l<sizer+size-1; l++)
          printf("-");
        printf("\n");
      }
      for (int jo=0; jo<size; jo++) {
        int j = js*size+jo;
        for (int ks=0; ks<size; ks++) {
          if (ks>0) printf("|");
          for (int ko=0; ko<size; ko++) {
            int k = ks*size+ko;
            cell_t &cell = w[j*sizer+k];
            if (!admi) {
              int v = cell.entry;
              if (v) {
                if (sizer<10) printf("%d",v);
                else printf("%.2d",cell.entry);
              } else {
                if (sizer<10) printf(".");
                else printf("..");
              }
            } else {
              printf("%d",cell.admissible.size());
            }
          }
        }
        printf("\n");
      }
    }
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>

  // Cells have two coordinate systems. (j=row,k=column) and
  // (q=square,c=relative-cell). The first one is
  // evident. For the second one the square index `q'
  // denotes in which of the 9 squares is the cell
  // (traversing rows first), and then a "relative cell
  // index" `c' which also is numbered traversing rows first.
  // So for instance cell (j=4,k=7) is the same as (q=5,c=4)
  void indx(int q,int c,int &j,int &k) {
    j = (q/size)*size + c/size;
    k = (q%size)*size + c%size;
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  // This routine applies all the rules in order to set all
  // entries that can be deduced from the already set ones.
  // return values are:
  // 1: applied rules lead to complete filling of the board
  // 0: applied rules lead to partial filling of the board
  // -1: board is overdetermined
  int apply_rules() {
    // set1 = number of cells set after this round
    // set0 = number of cells set before this round
    // round = index of current round
    int set1,set0=0,round=0;
    while (true) {
      // Initialize counter
      set1=0;      

      // Row check. For each row `j' and each entry `e'
      // revise the row to check if the number of cells
      // where entry `e' is admissible is 1. If this is
      // the case entry `e' goes in that cell. 
      for (int j=0; j<sizer; j++) {
        for (int e=1; e<=sizer; e++) {
          // `columns' stores the columns where
          // `e' is admissible
          set<int> columns;
          for (int k=0; k<sizer; k++) {
            cell_t &cell = w[j*sizer+k];
            if (cell.admissible.find(e)
                !=cell.admissible.end()) {
              columns.insert(k);
            }
          }

          // Check if board is over-determined
          if (columns.size()<1) return -1;

          // If only one column is admissible, then set
          // entry in that cell.
          if (columns.size()==1) {
            int k = *columns.begin();
            cell_t &cell = w[j*sizer+k];
            if (cell.entry==0) {
              set_entry(j,k,e);
              if (verbose)
                printf("row check, cell (%d,%d) set to %d\n",j,k,e);
            } else if (cell.entry != e) return -1;
          }
        }
      }

      // Column check. Idem as row-check but for columns
      for (int k=0; k<sizer; k++) {
        for (int e=1; e<=sizer; e++) {
          // Revise column `k' for entry `e'
          // if only one row is admissible
          // then set it
          set<int> rows;
          for (int j=0; j<sizer; j++) {
            cell_t &cell = w[j*sizer+k];
            if (cell.admissible.find(e)
                !=cell.admissible.end()) {
              rows.insert(j);
            }
          }

          // Check if board is over-determined
          if (rows.size()<1) return -1;

          if (rows.size()==1) {
            int j = *rows.begin();
            cell_t &cell = w[j*sizer+k];
            if (cell.entry==0) {
              set_entry(j,k,e);
              if (verbose)
                printf("column check, cell (%d,%d) set to %d\n",j,k,e);
            } else if(cell.entry != e) return -1;
          }
        }
      }

      // Square check. Idem as row-check but for squares
      for (int q=0; q<sizer; q++) {
        int j,k;
        for (int e=1; e<=sizer; e++) {
          // Revise square `q' for entry `e'
          // if only one cell is admissible
          // then set it
          set<int> cells;
          for (int c=0; c<sizer; c++) {
            // Convert (square,relcell) numbering
            // to (row,column) (see above)
            indx(q,c,j,k);
            cell_t &cell = w[j*sizer+k];
            if (cell.admissible.find(e)
                !=cell.admissible.end()) {
              cells.insert(c);
            }
          }

          // Check if board is over-determined
          if (cells.size()<1) return -1;

          if (cells.size()==1) {
            int c = *cells.begin();
            indx(q,c,j,k);
            cell_t &cell = w[j*sizer+k];
            if (cell.entry==0) {
              set_entry(j,k,e);
              if (verbose)
                printf("square check, cell (%d,%d) set to %d\n",j,k,e);
            } else if(cell.entry != e) return -1;
          }
        }
      }

      // Revise the cells. If the admissible set has only
      // one entry for that cell, then the entry goes there. 
      for (int j=0; j<sizer; j++) {
        for (int k=0; k<sizer; k++) {
          cell_t &cell = w[j*sizer+k];

          if (cell.admissible.size()<1) return -1;

          if (cell.entry==0 
              && cell.admissible.size()==1) {
            int v = *cell.admissible.begin();
            if (verbose)
              printf("cell check, cell (%d,%d) set to %d\n",j,k,v);
            set_entry(j,k,v);
          }
          set1 += (cell.entry>0);
        }
      }

      if (verbose)
        printf("round %d, set %d cells so far\n",
               round,set1);

      // If all cells have been set, then the problem was solved. 
      if (set1==sizeb) return 1;
      // If no new cell has been filled, then process has
      // stagnated, and we must start `guessing'. 
      if (set1==set0) return 0;

      // Update cycle variables
      set0=set1;
      round++;
    }
    return -1; // never should reach this point 
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  // Solves a sudoku problem. Tries to apply the rules until
  // the problem is solved or either stagnates. In the last
  // case, start guessing for the cell with lowest number of
  // admissible entries and continue. Returns number of
  // posible solutions. If the board is overdetermined then
  // return 0.
  void solve_aux() {

    if (!compute_all_solutions 
        && solutions.size()>1) return;
    int retval = apply_rules();
    if (retval==1) {
      solutions.insert(solutions.begin(),w);
      if (!compute_all_solutions 
          && solutions.size()>1) return;
    }
    if (retval==-1) return;

    int jmin=-1, kmin=-1, admiss;

    // Look for the cell not yet determined
    // with the lower number of admissible
    // values
    for (int j=0; j<sizer; j++) {
      for (int k=0; k<sizer; k++) {
        int cellindx = j*sizer+k, sz;
        cell_t &cell = w[cellindx];
        sz = cell.admissible.size();
        // warning: size==1 means the cell
        // has been already filled. Don't take
        // into account.
        if (sz>1 && (jmin==-1 || sz<admiss)) {
          jmin = j; kmin=k;
          admiss = sz;
        }
      }
    }

    // Didn't find a cell, the problem
    // is overdetermined. 
    if (!(admiss>1 && jmin>=0)) return;

    // Found a cell
    int cellmin = jmin*sizer+kmin;
    // This is the admissible set of values
    // for the cell
    set<int> s = w[cellmin].admissible;
    // Push current state into the stack
    state_stack.insert(state_stack.begin(),w);

    // Try each of the admissible values
    set<int>::iterator q = s.begin();
    while (q!=s.end()) {
      // Reset current state 
      w = *state_stack.begin();

      if (verbose) print();

      // Set entry to the guessed value
      set_entry(jmin,kmin,*q);

      if (verbose) {
        printf("guessing (%d,%d) set to %d, current board: \n",
               jmin,kmin,*q);
        print();
      }

      // Try to solve again (recursively).
      solve_aux();
      q++;
    }
    // Restore state
    state_stack.erase(state_stack.begin());
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  int solve() {
    state_stack.clear();
    solutions.clear();
    solve_aux();
    return solutions.size();
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  void print_solutions() {
    list<state_t >::iterator 
      q = solutions.begin();
    int j=1, n = solutions.size();
    if (n==0) 
      printf("No solutions found!!\n");
    while (q!=solutions.end()) {
      if (j>1) printf("-----\n");
      printf("Solution #%d/%d\n",j++,n);
      w = *q++;
      print();
    }
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  // Check for a random board derived from this initial board
  void random_board() {
    compute_all_solutions = 0;
    state_t wini = w;
    while (true) {
      w = wini;
      int nsol;
      while (true) {
        nsol = solve();
        printf("nsol %d\n",nsol);
        if (nsol<=1) break;
        
        // Count number of void cells
        set<int> void_cells;
        for (int j=0; j<sizeb; j++) 
          if (w[j].entry==0) void_cells.insert(j);
        
        // Pick a random void cell
        printf("void cells %d \n",void_cells.size());
        int c = rand_pick(void_cells);
        cell_t &cell = w[c];
        int e = rand_pick(cell.admissible);
        int 
          j = c/sizer,
          k = c % sizer;
        set_entry(j,k,e);
        printf("setting entry (%d,%d) to %d\n",j,k,e);
        // print();
      }
      if (nsol==1) break;
    }
  }

  int random_board2() {
    compute_all_solutions = 0;
    // verbose = 1;
    state_t state = w;
    int retval = random_board2_aux(state);
    w = state;
    printf("Initial board\n");
    print();
    solve();
    printf("Solved board\n");
    
    w = state;
    return retval;
  }

  int random_board2_aux(state_t &state) {
    w = state;
    int retval = solve();
    if (retval<=1) return retval;

    int jmin=-1, kmin=-1, admiss;

    // Look for the cell not yet determined
    // with the lower number of admissible
    // values
    w = state;
    for (int j=0; j<sizer; j++) {
      for (int k=0; k<sizer; k++) {
        int cellindx = j*sizer+k, sz;
        cell_t &cell = w[cellindx];
        sz = cell.admissible.size();
        // warning: size==1 means the cell
        // has been already filled. Don't take
        // into account.
        if (sz>1 && (jmin==-1 || sz<admiss)) {
          jmin = j; kmin=k;
          admiss = sz;
        }
      }
    }

    // Didn't find a cell, the problem
    // is overdetermined. 
    assert(admiss>1 && jmin>=0);

    // Found a cell
    int cellmin = jmin*sizer+kmin;
    // This is the admissible set of values
    // for the cell
    set<int> s = w[cellmin].admissible;

    // Try each of the admissible values
    set<int>::iterator q = s.begin();
    while (q!=s.end()) {
      // Reset current state 
      w = state;

      if (verbose) print();

      // Set entry to the guessed value
      set_entry(jmin,kmin,*q);
      state_t current = w;

      if (verbose) {
        printf("guessing (%d,%d) set to %d, current board: \n",
               jmin,kmin,*q);
        print();
      }

      // Try to solve again (recursively).
      int nsol = solve();
      printf("nsol %d\n",nsol);
      if (nsol==1) {
        state = current;
        return 1;
      }
 
     q++;
    }

    // Try each of the admissible values
    // 
    q = s.begin();
    while (q!=s.end()) {
      // Reset current state 
      w = state;

      if (verbose) print();

      // Set entry to the guessed value
      set_entry(jmin,kmin,*q);
      state_t current = w;

      if (verbose) {
        printf("guessing (%d,%d) set to %d, current board: \n",
               jmin,kmin,*q);
        print();
      }

      // Try to solve again (recursively).
      int nsol = random_board2_aux(current);
      printf("nsol %d\n",nsol);
      if (nsol==1) {
        state = current;
        return 1;
      }
 
     q++;
    }

    return 0;
  }
};

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void try_problem(const int *v,const char *descrip) {
  board_t board(3);
  board.init(v);
  board.compute_all_solutions = 1;
  printf("--------- %s --------\nInitial board: \n\n",descrip);
  board.print();
  int retval = board.solve();
  if (retval<0) printf("Overdetermined board!! retval %d\n",retval);
  else printf("\nTotal solutions %d\n\n",retval);
  board.print_solutions();
  printf("-----------------\n\n");
}

//--------------------------------------------------------------------
void test_boards() {

  board_t board(3);

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  int sdk8[] = {0,0,5,0,4,0,0,0,0,
                4,8,0,6,0,1,0,0,0,
                0,2,0,0,0,9,0,7,0,
                0,0,0,4,0,0,9,0,3,
                2,0,4,0,0,0,7,0,5,
                1,0,9,0,0,7,0,0,0,
                0,5,0,2,0,0,0,8,0,
                0,0,0,9,0,6,0,5,1,
                0,0,0,0,3,0,6,0,0};
  try_problem(sdk8,"Clarin 2008-01-03 basic");
  // Solved OK!! 
  // 695|743|128
  // 487|621|539
  // 321|589|476
  // -----------
  // 578|462|913
  // 234|198|765
  // 169|357|842
  // -----------
  // 956|214|387
  // 843|976|251
  // 712|835|694
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  int sdk9[] = {0,0,0,9,6,0,0,0,0,
                0,0,0,7,0,2,1,8,0,
                0,0,0,0,0,0,0,9,2,
                0,4,0,0,5,0,0,2,0,
                6,3,0,0,9,0,0,1,4,
                0,1,0,0,3,0,0,7,0,
                4,8,0,0,0,0,0,0,0,
                0,2,1,4,0,6,0,0,0,
                0,0,0,0,7,5,0,0,0};
  try_problem(sdk9,"Clarin 2008-01-03 intermediate");
  // Solved OK!! 
  //  1 7 2|9 6 8|4 5 3
  //  9 5 3|7 4 2|1 8 6
  //  8 6 4|5 1 3|7 9 2
  // ------------------
  //  7 4 8|6 5 1|3 2 9
  //  6 3 5|2 9 7|8 1 4
  //  2 1 9|8 3 4|6 7 5
  // ------------------
  //  4 8 7|3 2 9|5 6 1
  //  5 2 1|4 8 6|9 3 7
  //  3 9 6|1 7 5|2 4 8

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  int sdk10[] = {0,0,7,0,2,8,0,0,0,
                 4,0,3,7,0,0,0,8,0,
                 0,0,0,4,0,1,0,0,5,
                 1,0,2,0,0,0,4,3,0,
                 3,0,0,0,0,0,0,0,7,
                 0,4,5,0,0,0,8,0,1,
                 5,0,0,1,0,2,0,0,0,
                 0,6,0,0,0,3,7,0,2,
                 0,0,0,8,6,0,3,0,0};
  try_problem(sdk10,"// Clarin 2008-01-03 advanced");
  // Solved OK
  // 957|628|143
  // 413|759|286
  // 286|431|975
  // -----------
  // 172|586|439
  // 398|214|567
  // 645|397|821
  // -----------
  // 534|172|698
  // 861|943|752
  // 729|865|314

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  int sdk11[] = {1,0,0,0,0,8,6,0,0,
                 0,0,0,6,0,0,0,1,5,
                 0,0,0,0,0,0,4,7,0,
                 9,0,0,3,2,0,0,8,4,
                 0,0,1,0,0,0,3,0,0,
                 4,8,0,0,7,6,0,0,1,
                 0,2,4,0,0,0,0,0,0,
                 5,1,0,0,0,2,0,0,0,
                 0,0,7,8,0,0,0,0,6};
  try_problem(sdk11,"// Clarin 2008-01-04 basic");
  // Solved OK!! 
  // 149|758|632
  // 732|694|815
  // 865|213|479
  // -----------
  // 976|321|584
  // 251|489|367
  // 483|576|291
  // -----------
  // 624|137|958
  // 518|962|743
  // 397|845|126

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  int sdk12[] = {0,8,9,0,0,0,5,0,1,
                 6,0,0,0,3,1,2,0,0,
                 0,0,0,4,0,0,0,7,0,
                 0,6,4,0,2,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,
                 0,0,0,0,6,0,1,3,0,
                 0,1,0,0,0,9,0,0,0,
                 0,0,3,6,4,0,0,0,9,
                 7,0,2,0,0,0,4,6,0};
  try_problem(sdk12,"// Clarin 2008-01-04 intermediate");
  // 389|276|541
  // 647|531|298
  // 521|498|376
  // -----------
  // 164|325|987
  // 238|917|654
  // 975|864|132
  // -----------
  // 416|759|823
  // 853|642|719
  // 792|183|465

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  int sdk13[] = {9,0,0,6,7,4,0,0,0,
                 0,0,1,0,0,0,0,6,0,
                 0,0,0,0,1,9,0,8,0,
                 8,0,0,0,6,0,1,0,0,
                 0,0,6,5,0,1,2,0,0,
                 0,0,2,0,9,0,0,0,6,
                 0,4,0,3,8,0,0,0,0,
                 0,3,0,0,0,0,9,0,0,
                 0,0,0,9,4,5,0,0,2};
  try_problem(sdk13,"// Clarin 2008-01-04 advanced");
  // Solved OK!!
  // 983|674|521
  // 721|853|469
  // 654|219|387
  // -----------
  // 895|762|143
  // 476|531|298
  // 312|498|756
  // -----------
  // 249|387|615
  // 538|126|974
  // 167|945|832

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  int sdk14[] = {6,0,4,0,0,0,0,0,0,
                 9,0,0,0,6,5,1,0,0,
                 0,0,8,0,7,0,0,0,3,
                 0,0,7,0,0,0,6,5,0,
                 0,0,0,7,8,3,0,0,0,
                 0,2,9,0,0,0,3,0,0,
                 7,0,0,0,4,0,5,0,0,
                 0,0,5,2,3,0,0,0,1,
                 0,0,0,0,0,0,4,0,8};
  try_problem(sdk14,"Clarin 2008-01-06 basic");
  // Solved OK!!
  // 614|329|875
  // 973|865|142
  // 258|471|963
  // -----------
  // 837|912|654
  // 546|783|219
  // 129|654|387
  // -----------
  // 792|148|536
  // 485|236|791
  // 361|597|428

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  int sdk15[] = {0,0,0,7,9,5,0,0,0,
                 0,4,0,0,0,0,0,0,0,
                 0,6,7,0,0,0,5,0,9,
                 0,5,0,2,1,0,8,0,6,
                 0,2,0,0,5,0,0,3,0,
                 1,0,6,0,4,3,0,5,0,
                 8,0,4,0,0,0,7,6,0,
                 0,0,0,0,0,0,0,9,0,
                 0,0,0,1,7,8,0,0,0};
  try_problem(sdk15,"Clarin 2008-01-06 intermediate");
  // Solved OK!!
  // 281|795|643
  // 549|386|217
  // 367|421|589
  // -----------
  // 453|219|876
  // 928|657|431
  // 176|843|952
  // -----------
  // 814|932|765
  // 732|564|198
  // 695|178|324

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  int sdk16[] = {9,0,3,0,0,0,4,0,1,
                 2,0,0,0,0,9,0,8,0,
                 0,5,0,2,0,0,0,0,0,
                 6,0,2,0,0,7,0,4,0,
                 0,0,0,1,0,3,0,0,0,
                 0,3,0,6,0,0,5,0,7,
                 0,0,0,0,0,4,0,7,0,
                 0,7,0,9,0,0,0,0,8,
                 3,0,5,0,0,0,9,0,4};
  try_problem(sdk16,"Clarin 2008-01-06 advanced");
  // Solved OK!!
  // 983|765|421
  // 261|439|785
  // 754|218|639
  // -----------
  // 692|587|143
  // 547|193|862
  // 138|642|597
  // -----------
  // 819|354|276
  // 476|921|358
  // 325|876|914

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  int sdk17[] = {0,0,6,8,0,3,0,0,1,
                 5,7,0,0,2,0,8,0,0,
                 0,0,8,0,0,0,0,0,0,
                 2,0,0,0,9,0,0,7,0,
                 0,0,0,6,8,4,0,0,0,
                 0,5,0,0,3,0,0,0,9,
                 0,0,0,0,0,0,6,0,0,
                 0,0,5,0,7,0,0,2,8,
                 8,0,0,3,0,1,5,0,0};
  try_problem(sdk17,"Clarin 2008-01-07 basic");
  // Solved OK!!
  // 926|843|751
  // 571|926|843
  // 438|517|962
  // -----------
  // 283|195|476
  // 719|684|235
  // 654|732|189
  // -----------
  // 397|258|614
  // 165|479|328
  // 842|361|597

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  int sdk18[] = {0,1,0,0,9,8,0,0,7,
                 0,0,6,0,0,0,0,0,0,
                 7,0,3,0,6,0,1,0,0,
                 0,7,0,0,0,2,6,0,0,
                 0,0,0,0,3,0,0,0,0,
                 0,0,5,4,0,0,0,1,0,
                 0,0,2,0,4,0,3,0,5,
                 0,0,0,0,0,0,8,0,0,
                 4,0,0,9,1,0,0,2,0};
  try_problem(sdk18,"Clarin 2008-01-07 intermediate");
  // Solved OK!!
  // 214|398|567
  // 986|751|432
  // 753|264|189
  // -----------
  // 379|182|654
  // 641|539|278
  // 825|476|913
  // -----------
  // 162|847|395
  // 597|623|841
  // 438|915|726

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  int sdk19[] = {0,0,0,6,0,0,3,0,0,
                 0,3,7,0,0,0,9,6,0,
                 0,0,0,5,0,0,0,2,1,
                 7,8,0,0,0,0,1,0,0,
                 0,0,0,1,0,3,0,0,0,
                 0,0,9,0,0,0,0,7,4,
                 1,5,0,0,0,8,0,0,0,
                 0,9,3,0,0,0,7,5,0,
                 0,0,4,0,0,2,0,0,0};
  try_problem(sdk19,"Clarin 2008-01-07 advanced");
  // Solved OK!!
  // 521|649|387
  // 437|281|965
  // 968|537|421
  // -----------
  // 785|924|136
  // 246|173|598
  // 319|865|274
  // -----------
  // 152|798|643
  // 893|416|752
  // 674|352|819

  int sdk20[] = {0,2,0,0,3,0,7,0,0,
                 1,0,0,0,0,0,5,4,0,
                 0,4,0,0,8,7,0,0,9,
                 0,0,9,3,0,0,0,6,0,
                 0,0,0,0,4,0,0,0,0,
                 0,6,0,0,0,9,8,0,0,
                 7,0,0,8,1,0,0,3,0,
                 0,9,1,0,0,0,0,0,4,
                 0,0,8,0,9,0,0,5,0};
  try_problem(sdk20,"Clarin 2008-01-08 basic");
  // Solved OK!!
  // 926|435|718
  // 187|962|543
  // 543|187|629
  // -----------
  // 219|378|465
  // 875|641|392
  // 364|529|871
  // -----------
  // 752|814|936
  // 691|753|284
  // 438|296|157

  int sdk21[] = {0,0,0,0,2,0,0,0,0,
                 7,0,0,0,0,9,4,0,8,
                 0,1,0,4,0,7,5,0,0,
                 0,2,0,9,0,0,0,0,6,
                 0,0,0,0,1,0,0,0,0,
                 8,0,0,0,0,6,0,2,0,
                 0,0,8,1,0,3,0,7,0,
                 6,0,5,8,0,0,0,0,3,
                 0,0,0,0,5,0,0,0,0};
  try_problem(sdk21,"Clarin 2008-01-08 intermediate");
  // Solved OK!!
  // 584|321|967
  // 732|569|418
  // 916|487|532
  // -----------
  // 421|938|756
  // 367|215|894
  // 859|746|321
  // -----------
  // 248|193|675
  // 695|872|143
  // 173|654|289
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  int sdk22[] = {1,7,0,0,0,0,5,0,4,
                 0,0,4,0,7,0,9,2,0,
                 0,0,0,0,5,4,3,0,7,
                 0,0,0,0,6,1,0,0,0,
                 0,0,6,0,0,0,2,0,0,
                 0,0,0,9,8,0,0,0,0,
                 8,0,7,3,4,0,0,0,0,
                 0,3,1,0,2,0,6,0,0,
                 5,0,9,0,0,0,0,8,3};
  try_problem(sdk22,"Clarin 2008-01-08 advanced");
  // Solved OK!!
  // 173|298|564
  // 654|173|928
  // 298|654|317
  // -----------
  // 742|561|839
  // 986|437|251
  // 315|982|746
  // -----------
  // 867|345|192
  // 431|829|675
  // 529|716|483

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  int sdk23[] = {5,3,0,0,7,0,0,0,0,
                 6,0,0,1,9,5,0,0,0,
                 0,9,8,0,0,0,0,6,0,
                 8,0,0,0,6,0,0,0,3,
                 4,0,0,8,0,3,0,0,1,
                 7,0,0,0,2,0,0,0,6,
                 0,6,0,0,0,0,2,8,0,
                 0,0,0,4,1,9,0,0,5,
                 0,0,0,0,8,0,0,7,9};

  try_problem(sdk23,"From Wikipedia Sudoku page");
  // Solved OK!!
  // 534|678|912
  // 672|195|348
  // 198|342|567
  // -----------
  // 859|761|423
  // 426|853|791
  // 713|924|856
  // -----------
  // 961|537|284
  // 287|419|635
  // 345|286|179

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  int blank[] = {0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0};
  
}

void test_boards2() {
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  int sdk1[] = {0,0,0,6,0,0,3,0,0,
                0,0,7,0,0,0,9,6,0,
                0,0,0,5,0,0,0,2,1,
                7,0,0,0,0,0,1,0,0,
                0,0,0,1,0,3,0,0,0,
                0,0,9,0,0,0,0,7,4,
                1,5,0,0,0,8,0,0,0,
                0,9,3,0,0,0,7,5,0,
                0,0,4,0,0,2,0,0,0};
  try_problem(sdk1,"Should be underdetermined (8 solutions)");

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  int sdk2[] = {0,0,2,6,0,0,3,0,0,
                0,3,7,0,0,0,9,6,0,
                0,0,0,5,0,0,0,2,1,
                7,8,0,0,0,0,1,0,0,
                0,0,0,1,0,3,0,0,0,
                0,0,9,0,0,0,0,7,4,
                1,5,0,0,0,8,0,0,0,
                0,9,3,0,0,0,7,5,0,
                0,0,4,0,0,2,0,0,0};
  try_problem(sdk2,"Should be overdetermined (0 solutions)");

}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void gen_random_board() {
  board_t board(3);
  
  // This one has exactly one solution
//   int sdk[] = {1,7,0,0,0,0,5,0,4,
//                0,0,4,0,7,0,9,2,0,
//                0,0,0,0,5,4,3,0,7,
//                0,0,0,0,6,1,0,0,0,
//                0,0,6,0,0,0,2,0,0,
//                0,0,0,9,8,0,0,0,0,
//                8,0,7,3,4,0,0,0,0,
//                0,3,1,0,2,0,6,0,0,
//                5,0,9,0,0,0,0,8,3};

  int sdk[] = {1,7,0,0,0,0,5,0,0,
               0,0,4,0,0,0,9,2,0,
               0,0,0,0,5,4,3,0,7,
               0,0,0,0,0,1,0,0,0,
               0,0,6,0,0,0,2,0,0,
               0,0,0,0,8,0,0,0,0,
               8,0,7,3,4,0,0,0,0,
               0,3,0,0,2,0,6,0,0,
               5,0,9,0,0,0,0,8,3};

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  board.init(sdk);
  board.random_board2();
  board.print_solutions();
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  docver_print();
  // gen_random_board();
  test_boards();
  // test_boards2();

  exit(0);
}

