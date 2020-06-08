// This Program will calculate the minimum path hamiltonian circuit
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>

// funtions used in the program

int col_num(char *input_filename);
int row_num(char *input_filename);
void all_possible_permut(int n, int p[], int *more);
double large_num();
double *read_data_file(char *input_filename, int m, int n);
void read_data_head(char *input_filename, int *m, int *n);
void print_file(int m, int n, double a[], char *title);
void print_file_some(int m, int n, double a[], int row_first, int col_first, int row_last, int col_last, char *title);
int right_space_trim(char *s);
double read_from_str(char *s, int *lchar, int *error);
int read_from_strvec(char *s, int n, double rvec[]);
int str_word_count(char *s);

int main(){
  double *distance;
  char nodetable_file[255];
  int i, i1, i2, m, more, n, *p, *p_min, paths;
  double total, total_ave, total_max, total_min;
  
  printf("Enter the name of the file containing the city-to-city distance table.\n");   // get the node table from the file
  scanf("%s", nodetable_file);

  read_data_head(nodetable_file, &m, &n);        //  func to read file header ,  produce an error if columns and record in table are <=0

  printf("\n");
  printf("Number of cities is %d\n",n);

  distance = read_data_file(nodetable_file, n, n);   // func to read node table from file
  print_file(n, n, distance, "Distance matrix:");    // func to print the node table

  total_min = large_num();   // assign a maximum value to a variable to calculate minimum path
  total_max = - large_num();   // assign a minimm value to a variable to calculate maximum path
  total_ave = 0.0;          

  more = 0;
  p = ( int * ) malloc ( n * sizeof ( int ) );    
  p_min = ( int * ) malloc ( n * sizeof ( int ) );

  paths = 0;

  for( ; ; ){                        // loop executed infinitely until breakout internally
    all_possible_permut(n, p, &more);   // func  to calculate all possible combination of paths
    paths = paths + 1;
    total = 0.0;
    i1 = n - 1;
    for(i2 = 0; i2 < n; i2++){
      total = total + distance[p[i1]+p[i2]*n];
      i1 = i2;
    }

    total_ave = total_ave + total;    //

    if(total_max < total){    //
      total_max = total;
    }

    if(total < total_min){
      total_min = total;         // new path < minimum until now  => new path is new minimum
      for(i=0; i<n; i++ ){
        p_min[i] = p[i];
      }
    }
   if (!more){
      break;                     // exit condition for infinite loop
    }
 }
  
  total_ave = total_ave/(double)(paths);   //
  
  printf(" Route  From  To  Cost\n");
  printf("\n");
  i1 = n - 1;
  for(i2=0; i2<n; i2++){
    printf(" %4d   %2d   %2d    %g\n", i2 +1, p_min[i1], p_min[i2], distance[p_min[i1]+p_min[i2]*n] );     // prints Routing table
    i1 = i2;
  }
  printf("\n");
  printf("  Minimum Route cost :     %g\n", total_min);   // prints cost of the path choosen(minimum)

  printf("  Number of paths checked = %d\n", paths); 
  printf("  Minimum length = %g\n", total_min);
  printf("  Average length = %g\n", total_ave);     //
  printf("  Maximum length = %g\n", total_max);     //

  free(distance);      // freeing up memory
  free (p);
  free (p_min);

  printf("\n");
  printf("  Travelling Salesman Problem Implementation for Calculating Optimal Path\n");
  printf("  Program Termination\n" );
  return 0;
}


int equi_ch(char ch1, char ch2)   // Returns True if two characters are equal
{
  int value;
  if(97<=ch1 && ch1<=122){     // converts input1 to uppercase if it is in lowercase
    ch1 = ch1 - 32;
  }  
  if(97<=ch2 && ch2<=122){    // converts input2 to uppercase if it is in lowercase
    ch2 = ch2 - 32;
  }     
  if(ch1 == ch2){           // returns 1 if input1 == input2
    value = 1;
  }
  else{
    value = 0;
  }
  return value;
}


int ch_equi_num(char ch){    // Returns natural value of a decimal number
  int digit;

  if('0'<=ch && ch<='9'){
    digit = ch - '0';
  }
  else if(ch == ' '){
    digit = 0;
  }
  else{
    digit = -1;
  }
  return digit;
}


int col_num(char *filename){   // counts the number of columns from first row of the file
# define LINE_MAX 255
  int column_num, got_one;
  char *error;
  FILE *input;
  char line[LINE_MAX];

  input = fopen(filename, "r");      // opening the file
   
   if(!input){                       // execute if file not opened or not found
    fprintf(stderr, "col_num - Fatal error!\n" );
    fprintf(stderr, "  Could not open the input file: \"%s\"\n", filename); 
    exit(1);
  }
  
  got_one = 0;
  for( ; ; ){                    // will execute until loop not breaken internally by break or goto statement
     error = fgets(line, LINE_MAX, input);

   if(!error){                 // terminate from loop if error = 0
      break;
    }
    if(right_space_trim(line) == 0){   // string is entirely blank if this executes
      continue;
    }
    if(line[0] == '#'){        // t check for comments or line that user doesnot want to read
      continue;
    }
    got_one = 1;       // will execute if error !=0
    break;             // terminate from loop
 }
  fclose (input);
  if(got_one == 0){       // if error = 0 then got_one = 0 => file does not contain any data
    fprintf(stderr, "col_num - Warning!\n");
    fprintf(stderr, "  The file does not seem to contain any data.\n");
    exit(1);
  }
  column_num = str_word_count(line);

  return column_num;
# undef LINE_MAX
}

int row_num(char *filename){
# define LINE_MAX 255

  int bad_num, comment_num, i, record_num, row_num;
  char *error;
  FILE *input;
  char line[LINE_MAX];
  
  row_num = 0;
  comment_num = 0;
  record_num = 0;
  bad_num = 0;

  input = fopen(filename, "r" );

  if(!input){
    fprintf(stderr, "\n" );
    fprintf(stderr, "row_num - Fatal error!\n");
    fprintf(stderr, "  Could not open the input file: \"%s\"\n", filename );
    exit(1);
  }

  for ( ; ; ){
    error = fgets(line, LINE_MAX, input);
    if (!error){
      break;
    }

    record_num = record_num + 1;

    if(line[0] == '#'){
      comment_num = comment_num + 1;
      continue;
    }

    if(right_space_trim(line) == 0){
      comment_num = comment_num + 1;
      continue;
    }

    row_num = row_num + 1;
  }
  fclose(input);
  return row_num;

# undef LINE_MAX
}


void all_possible_permut(int n, int p[], int *more){
  int i, m2, n2, q, s, t, temp;
  static int nfact = 0;
  static int rank = 0;

  if(!(*more)){
    for (i = 0; i < n; i++)
    {
      p[i] = i;
    }
    *more = 1;
    rank = 1;

    nfact = 1;
    for(i = 1; i <= n; i++){
      nfact = nfact * i;
    }
  }
  else{
    n2 = n;
    m2 = rank;
    s = n;

    for( ; ; ){
      q = m2 % n2;
      t = m2 % (2 * n2);

      if(q != 0){
        break;
      }
      if(t == 0){
        s = s - 1;
      }
      m2 = m2 / n2;
      n2 = n2 - 1;
    }
    if(q == t){
      s = s - q;
    }
    else{
      s = s + q - n2;
    }

    temp = p[s-1];
    p[s-1] = p[s];
    p[s] = temp;

    rank = rank + 1;

    if(rank == nfact){
      *more = 0;
    }
  }
  return;
}


double large_num(){
  double value;
  value = 1.0E+30;
  return value;
}


double *read_data_file(char *filename, int m, int n){
# define LINE_MAX 255

  int error, i, j;
  char *got_string, line[255];
  FILE *input; 
  double *table, *x;

  input = fopen(filename, "r");
  if(!input){
    fprintf(stderr, " read_data_file - Fatal error!\n");
    fprintf(stderr, " Could not open the input file: \"%s\"\n", filename);
    exit(1);
  }

  table = ( double * ) malloc ( m * n * sizeof ( double ) );
  x = ( double * ) malloc ( m * sizeof ( double ) );
  j = 0;

  while(j<n){
    got_string = fgets(line, LINE_MAX, input);
    if(!got_string){
      break;
    }
    if(line[0] == '#' || right_space_trim(line) == 0){
      continue;
    }
    error = read_from_strvec(line, m, x);
    if(error == 1){
      continue;
    }
    for(i = 0; i < m; i++){
      table[i+j*m] = x[i];
    }
    j = j + 1;
  }

  fclose(input);
  free(x);

  return table;
# undef LINE_MAX
}

 
void read_data_head(char *filename, int *m, int *n){
  *m = col_num(filename);

  if(*m<=0){
    fprintf(stderr, "read_data_head - Fatal error!\n");
    fprintf(stderr, "  col_num failed.\n");
    exit(1);
  }

  *n = row_num(filename);

  if(*n<=0){
    fprintf(stderr, "read_data_head - Fatal error!\n");
    fprintf(stderr, "  row_num failed.\n");
    exit(1);
  }
  return;
}

void print_file(int m, int n, double a[], char *title){
  print_file_some(m, n, a, 1, 1, m, n, title);

  return;
}


void print_file_some(int m, int n, double a[], int row_first, int col_first, int row_last, int col_last, char *title){
# define INCX 5    // to print upto 5 columns in a single line

  int i, i2hi, i2lo, j, j2hi, j2lo;
  fprintf(stdout, "%s\n", title);

  if(m<=0 || n<=0){
    fprintf(stdout, " (None)\n");
    return;
  }
  
  for(j2lo=col_first; j2lo<=col_last; j2lo = j2lo + INCX){    // prints column of the matrix in strips of n
    j2hi = j2lo + INCX - 1;
    if(n<j2hi){
      j2hi = n;
    }
    if(col_last<j2hi){
      j2hi = col_last;
    }

    fprintf(stdout, "  Col:  ");   // write header for each column
    for(j=j2lo; j<=j2hi; j++){
      fprintf(stdout, "  %7d    ", j-1);
    }
    fprintf(stdout, "\n" );
    fprintf(stdout, "  Row\n" );
    fprintf(stdout, "\n" );
    
    if(1<row_first){         //  determine range of rows in strips
      i2lo = row_first;
    }
    else{
      i2lo = 1;
    }
    if(m<row_last){
      i2hi = m;
    }
    else{
      i2hi = row_last;
    }

    for(i = i2lo; i <= i2hi; i++ ){      // will print upto 5 enteries in a row other enterie will be shown in a new line.
      fprintf(stdout, "%5d:", i - 1);
      for(j = j2lo; j <= j2hi; j++){
        fprintf(stdout, "  %14g", a[i-1+(j-1)*m]);
      }
      fprintf(stdout, "\n");
    }
  }

  return;
# undef INCX
}


int right_space_trim(char *s){
  int n;
  char *t;

  n = strlen(s);
  t = s + strlen(s) - 1;

  while(0<n) {
    if(*t != ' '){
      return n;
    }
    t--;
    n--;
  }
  return n;
}


double read_from_str(char *s, int *lchar, int *error){
  char c;
  int ihave, isgn, iterm, jbot, jsgn, jtop, nchar, ndig;
  double r, rbot, rexp, rtop;
  char TAB = 9;

  nchar = right_space_trim(s);
  *error = 0;
  r = 0.0;
  *lchar = -1;
  isgn = 1;
  rtop = 0.0;
  rbot = 1.0;
  jsgn = 1;
  jtop = 0;
  jbot = 1;
  ihave = 1;
  iterm = 0;

  for ( ; ; ){
    c = s[*lchar+1];
    *lchar = *lchar + 1;

    if(c == ' ' || c == TAB){     //   Blank or TAB character.
      if(ihave == 2){}
      else if(ihave == 6 || ihave == 7){
        iterm = 1;
      }
      else if(1 < ihave){
        ihave = 11;
      }
    }

    else if(c == ',' || c == ';'){    // comma or semicolon 
      if(ihave != 1){
        iterm = 1;
        ihave = 12;
        *lchar = *lchar + 1;
      }
    }

    else if(c == '-'){     // for minus sign
      if(ihave == 1){
        ihave = 2;
        isgn = -1;
      }
      else if(ihave == 6){
        ihave = 7;
        jsgn = -1;
      }
      else{
        iterm = 1;
      }
    }
    else if(c == '+'){    // for plus sign
      if(ihave == 1){
        ihave = 2;
      }
      else if(ihave == 6){
        ihave = 7;
      }
      else{
        iterm = 1;
      }
    }
	else if(c == '.'){   // for decimal operator
      if(ihave < 4){
        ihave = 4;
      }
      else if(6 <= ihave && ihave <= 8){
        ihave = 9;
      }
      else{
        iterm = 1;
      }
    }
    else if(equi_ch( c, 'E') || equi_ch(c, 'D')){   // exponent marker
      if(ihave < 6){
        ihave = 6;
      }
      else{
        iterm = 1;
      }
    }
    else if(ihave < 11 && '0' <= c && c <= '9'){   // digit
      if(ihave <= 2){
        ihave = 3;
      }
      else if(ihave == 4){
        ihave = 5;
      }
      else if(ihave == 6 || ihave == 7){
        ihave = 8;
      }
      else if(ihave == 9){
        ihave = 10;
      }

      ndig = ch_equi_num(c);

      if(ihave == 3){
        rtop = 10.0 * rtop + ( double ) ndig;
      }
      else if(ihave == 5){
        rtop = 10.0 * rtop + ( double ) ndig;
        rbot = 10.0 * rbot;
      }
      else if(ihave == 8){
        jtop = 10 * jtop + ndig;
      }
      else if(ihave == 10){
        jtop = 10 * jtop + ndig;
        jbot = 10 * jbot;
      }
    }
    else{                // anything else is readed as terminator
      iterm = 1;
    }
    if(iterm == 1 || nchar <= *lchar + 1){  // gets the next char if terminator is not seen and string is not examined completely
      break; 
    }
 }
 if(iterm != 1 && (*lchar) + 1 == nchar){  // If we haven't seen a terminator, and we have examined the entire string, then we're done
    *lchar = nchar;
  }
  if(ihave == 1 || ihave == 2 || ihave == 6 || ihave == 7)
  {
    *error = 1;
    return r;
  }
  if(jtop == 0){   // let's assume anything less than 1.0E-20 is zero.
    rexp = 1.0;
  }
  else{
    if(jbot == 1){
      if(jsgn * jtop < -20){
        rexp = 0.0;
      }
      else{
        rexp = pow((double)10.0, (double)(jsgn * jtop));
      }
    }
    else{
      if(jsgn * jtop < -20 * jbot){
        rexp = 0.0;
      }
      else{
        rexp = jsgn * jtop;
        rexp = rexp / jbot;
        rexp = pow ( ( double ) 10.0, ( double ) rexp );
      }
    }
  }
  r = isgn * rexp * rtop / rbot;
  return r;
}

int read_from_strvec(char *s, int n, double rvec[]){
  int error, i, lchar;

  error = 0;

  for(i = 0; i < n; i++){
    rvec[i] = read_from_str(s, &lchar, &error);

    if(error){
      return error;
    }
    s = s + lchar;
  }
  return error;
}

int str_word_count(char *s){
  int blank, i, word_num;

  word_num = 0;
  blank = 1;

  while(*s){
    if(*s == ' ' || *s == '\n'){
      blank = 1;
    }
    else if(blank){
      word_num = word_num + 1;
      blank = 0;
    }
    *s++;
  }
  return word_num;
}
