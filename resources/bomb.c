array_123[16] = { 105, 115, 114, 118, 101, 97, 119, 104, 111, 98, 112, 110, 117, 116, 102, 103 };
// for phase 5 : i s r v e a w h o b p n u t f g
// so we need to get indexes 15, 0, 5, 11, 13, 1 to get "giants"

int node1; // for phase 6

int __cdecl main(int argc, const char **argv, const char **envp)
{
  _BYTE *line; // eax
  char *v4; // eax
  char *v5; // eax
  char *v6; // eax
  _BYTE *v7; // eax
  char *v8; // eax

  if ( argc == 1 )
  {
    infile = (_IO_FILE *)stdin;
  }
  else
  {
    if ( argc != 2 )
    {
      printf("Usage: %s [<input_file>]\n", *argv);
      exit(8);
    }
    infile = fopen(argv[1], "r");
    if ( !infile )
    {
      printf("%s: Error: Couldn't open %s\n", *argv, argv[1]);
      exit(8);
    }
  }
  initialize_bomb();
  printf("Welcome this is my little bomb !!!! You have 6 stages with\n");
  printf("only one life good luck !! Have a nice day!\n");
  line = (_BYTE *)read_line();
  phase_1(line);
  phase_defused();
  printf("Phase 1 defused. How about the next one?\n");
  v4 = (char *)read_line();
  phase_2(v4);
  phase_defused();
  printf("That's number 2.  Keep going!\n");
  v5 = (char *)read_line();
  phase_3(v5);
  phase_defused();
  printf("Halfway there!\n");
  v6 = (char *)read_line();
  phase_4(v6);
  phase_defused();
  printf("So you got that one.  Try this one.\n");
  v7 = (_BYTE *)read_line();
  phase_5(v7);
  phase_defused();
  printf("Good work!  On to the next...\n");
  v8 = (char *)read_line();
  phase_6(v8);
  phase_defused();
  return 0;
}
// 804B648: using guessed type int stdin;

//----- (08048B20) --------------------------------------------------------
int __cdecl phase_1(_BYTE *a1)
{
  int result; // eax

  result = strings_not_equal(a1, "Public speaking is very easy.");
  if ( result )
    explode_bomb();
  return result;
}

//----- (08048B48) --------------------------------------------------------
int __cdecl phase_2(char *s)
{
  int i; // ebx
  int result; // eax
  int v3[6]; // [esp+10h] [ebp-18h] BYREF

  read_six_numbers(s, (int)v3);
  if ( v3[0] != 1 )
    explode_bomb();
  for ( i = 1; i <= 5; ++i )
  {
    result = v3[i - 1] * (i + 1);
    if ( v3[i] != result )
      explode_bomb();
  }
  return result;
}
// 8048B48: using guessed type int var_18[6];

//----- (08048B98) --------------------------------------------------------
int __cdecl phase_3(char *s)
{
  int result; // eax
  char v2; // bl
  int v3; // [esp+Ch] [ebp-Ch] BYREF
  char v4; // [esp+13h] [ebp-5h] BYREF
  int v5; // [esp+14h] [ebp-4h] BYREF

  if ( sscanf(s, "%d %c %d", &v3, &v4, &v5) <= 2 )
    explode_bomb();
  result = v3;
  switch ( v3 )
  {
    case 0:
      v2 = 113;
      if ( v5 != 777 )
        explode_bomb();
      return result;
    case 1:
      v2 = 98;
      if ( v5 != 214 )
        explode_bomb();
      return result;
    case 2:
      v2 = 98;
      if ( v5 != 755 )
        explode_bomb();
      return result;
    case 3:
      v2 = 107;
      if ( v5 != 251 )
        explode_bomb();
      return result;
    case 4:
      v2 = 111;
      if ( v5 != 160 )
        explode_bomb();
      return result;
    case 5:
      v2 = 116;
      if ( v5 != 458 )
        explode_bomb();
      return result;
    case 6:
      v2 = 118;
      if ( v5 != 780 )
        explode_bomb();
      return result;
    case 7:
      v2 = 98;
      if ( v5 != 524 )
        explode_bomb();
      return result;
    default:
      explode_bomb();
  }
  if ( v2 != v4 )
    explode_bomb();
  return result;
}

//----- (08048CA0) --------------------------------------------------------
int __cdecl func4(int a1)
{
  int v1; // esi

  if ( a1 <= 1 )
    return 1;
  v1 = func4(a1 - 1);
  return v1 + func4(a1 - 2);
}

//----- (08048CE0) --------------------------------------------------------
int __cdecl phase_4(char *s)
{
  int result; // eax
  int v2; // [esp+14h] [ebp-4h] BYREF

  if ( sscanf(s, "%d", &v2) != 1 || v2 <= 0 )
    explode_bomb();
  result = func4(v2);
  if ( result != 55 )
    explode_bomb();
  return result;
}

//----- (08048D2C) --------------------------------------------------------
int __cdecl phase_5(_BYTE *a1)
{
  int i; // edx
  int result; // eax
  char v3[8]; // [esp+10h] [ebp-8h] BYREF

  if (string_length(a1) != 6)
    explode_bomb();
  for ( i = 0; i <= 5; ++i )
    v3[i] = array_123[a1[i] & 0xF];
  v3[6] = 0;
  result = strings_not_equal(v3, "giants");
  if ( result )
    explode_bomb();
  return result;
}
// 804B220: using guessed type _BYTE array_123[16];

//----- (08048D98) --------------------------------------------------------
int __cdecl phase_6(char *s)
{
  int i; // edi
  int j; // ebx
  int k; // edi
  int *v4; // esi
  int m; // ebx
  int v6; // esi
  int n; // edi
  int v8; // eax
  int v9; // esi
  int ii; // edi
  int result; // eax
  int v12; // [esp+24h] [ebp-34h]
  int v13[6]; // [esp+28h] [ebp-30h]
  int input[6]; // [esp+40h] [ebp-18h] BYREF

  read_six_numbers(s, (int)input);
  for ( i = 0; i <= 5; ++i )     // 6 nombres entre 1 et 6, pas de doubles
  {
    if ( (unsigned int)(input[i] - 1) > 5 )
      explode_bomb();
    for ( j = i + 1; j <= 5; ++j )
    {
      if ( input[i] == input[j] )
        explode_bomb();
    }
  }
  for ( k = 0; k <= 5; ++k )
  {
    v4 = &node1;
    for ( m = 1; m < input[k]; ++m )
      v4 = (int *)v4[2];
    v13[k] = (int)v4;
  }
  v6 = v13[0];
  v12 = v13[0];
  for ( n = 1; n <= 5; ++n )
  {
    v8 = v13[n];
    *(int *)(v6 + 8) = v8;
    v6 = v8;
  }
  *(int *)(v8 + 8) = 0;
  v9 = v12;
  for ( ii = 0; ii <= 4; ++ii )
  {
    result = *(int *)v9;
    if ( *(int *)v9 < **(int **)(v9 + 8) )
      explode_bomb();
    v9 = *(int *)(v9 + 8);
  }
  return result;
}
// 8048D98: using guessed type int var_18[6];
// 8048D98: using guessed type int var_30[6];

//----- (08048E94) --------------------------------------------------------
int __cdecl fun7(int *a1, int a2)
{
  if ( !a1 )
    return -1;
  if ( a2 < *a1 )
    return 2 * fun7(a1[1], a2);
  if ( a2 == *a1 )
    return 0;
  return 2 * fun7(a1[2], a2) + 1;
}

//----- (08048EE8) --------------------------------------------------------
void secret_phase()
{
  const char *line; // eax
  int v1; // ebx

  line = (const char *)read_line();
  v1 = __strtol_internal(line, 0, 10, 0);
  if ( (unsigned int)(v1 - 1) > 0x3E8 )
    explode_bomb();
  if ( fun7(n1, v1) != 7 )
    explode_bomb();
  printf("Wow! You've defused the secret stage!\n");
  phase_defused();
}
// 804B320: using guessed type int n1[8];

//----- (08048F50) --------------------------------------------------------
void __cdecl __noreturn sig_handler(int a1)
{
  printf("So you think you can stop the bomb with ctrl-c, do you?\n");
  sleep(3u);
  printf("Well...");
  fflush(stdout);
  sleep(1u);
  printf("OK. :-)\n");
  exit(16);
}

//----- (08048FB4) --------------------------------------------------------
void __cdecl __noreturn invalid_phase(const char *a1)
{
  printf("Invalid phase%s\n", a1);
  exit(8);
}

//----- (08048FD8) --------------------------------------------------------
int __cdecl read_six_numbers(char *s, int a2)
{
  int result; // eax

  result = sscanf(s, "%d %d %d %d %d %d", a2, a2 + 4, a2 + 8, a2 + 12, a2 + 16, a2 + 20);
  if ( result <= 5 )
    explode_bomb();
  return result;
}

//----- (08049018) --------------------------------------------------------
int __cdecl string_length(_BYTE *a1)
{
  _BYTE *v1; // edx
  int result; // eax

  v1 = a1;
  for ( result = 0; *v1; ++result )
    ++v1;
  return result;
}

//----- (08049030) --------------------------------------------------------
int __cdecl strings_not_equal(_BYTE *a1, _BYTE *a2)
{
  int v2; // ebx
  _BYTE *v4; // edx
  _BYTE *v5; // ecx

  v2 = string_length(a1);
  if ( v2 != string_length(a2) )
    return 1;
  v4 = a1;
  v5 = a2;
  if ( *a1 )
  {
    while ( *v4 == *v5 )
    {
      ++v4;
      ++v5;
      if ( !*v4 )
        return 0;
    }
    return 1;
  }
  return 0;
}

//----- (0804908C) --------------------------------------------------------
int __cdecl open_clientfd(char *name, __int16 a2)
{
  int v2; // esi
  struct hostent *v3; // ebx
  struct sockaddr s; // [esp+18h] [ebp-10h] BYREF

  v2 = socket(2, 1, 0);
  if ( v2 < 0 )
  {
    printf("Bad host (1).\n");
    exit(8);
  }
  v3 = gethostbyname(name);
  if ( !v3 )
  {
    printf("Bad host (2).\n");
    exit(8);
  }
  bzero(&s, 0x10u);
  s.sa_family = 2;
  bcopy(*(const void **)v3->h_addr_list, &s.sa_data[2], v3->h_length);
  *(_WORD *)s.sa_data = __ROR2__(a2, 8);
  if ( connect(v2, &s, 0x10u) < 0 )
  {
    printf("Bad host (3).\n");
    exit(8);
  }
  return v2;
}

//----- (08049160) --------------------------------------------------------
__sighandler_t initialize_bomb()
{
  return signal(2, (__sighandler_t)sig_handler);
}

//----- (0804917C) --------------------------------------------------------
int __cdecl blank_line(_BYTE *a1)
{
  _BYTE *v1; // edx
  int v2; // eax

  v1 = a1;
  if ( !*a1 )
    return 1;
  while ( 1 )
  {
    v2 = (char)*v1++;
    if ( (*(_BYTE *)(_ctype_b + 2 * v2 + 1) & 0x20) == 0 )
      break;
    if ( !*v1 )
      return 1;
  }
  return 0;
}
// 804B644: using guessed type int _ctype_b;

//----- (080491B0) --------------------------------------------------------
char *skip()
{
  char *v0; // eax
  char *v1; // ebx

  do
  {
    v0 = fgets((char *)(80 * num_input_strings + 134526592), 80, infile);
    v1 = v0;
  }
  while ( v0 && blank_line(v0) );
  return v1;
}
// 804B480: using guessed type int num_input_strings;

//----- (080491FC) --------------------------------------------------------
int read_line()
{
  unsigned int v0; // eax
  unsigned int v1; // edi
  int v2; // eax
  int result; // eax

  if ( !skip() )
  {
    if ( infile == (_IO_FILE *)stdin )
      goto LABEL_6;
    if ( getenv("GRADE_BOMB") )
      exit(0);
    infile = (_IO_FILE *)stdin;
    if ( !skip() )
    {
LABEL_6:
      printf("Error: Premature EOF on stdin\n");
      explode_bomb();
    }
  }
  v0 = strlen(&input_strings[80 * num_input_strings]) + 1;
  v1 = v0 - 1;
  if ( v0 == 80 )
  {
    printf("Error: Input line too long\n");
    explode_bomb();
  }
  v2 = 80 * num_input_strings;
  byte_804B67F[v1 + v2] = 0;
  result = v2 + 134526592;
  ++num_input_strings;
  return result;
}
// 804B480: using guessed type int num_input_strings;
// 804B648: using guessed type int stdin;

//----- (080492C0) --------------------------------------------------------
int __cdecl send_msg(int a1)
{
  int v1; // edi
  FILE *v2; // eax
  FILE *v3; // esi
  const char *v4; // eax
  const char *v5; // eax
  int v6; // edx
  int v7; // ebx
  int result; // eax
  char dest[80]; // [esp+18h] [ebp-50h] BYREF

  v1 = dup(0);
  if ( v1 == -1 )
  {
    printf("ERROR: dup(0) error\n");
    exit(8);
  }
  if ( close(0) == -1 )
  {
    printf("ERROR: close error\n");
    exit(8);
  }
  v2 = tmpfile();
  v3 = v2;
  if ( !v2 )
  {
    printf("ERROR: tmpfile error\n");
    exit(8);
  }
  fprintf(v2, "Subject: Bomb notification\n");
  fprintf(v3, "\n");
  v4 = (const char *)cuserid(0);
  if ( v4 )
    strcpy(dest, v4);
  else
    strcpy(dest, "nobody");
  v5 = "exploded";
  if ( a1 )
    v5 = "defused";
  fprintf(v3, "bomb-header:%s:%d:%s:%s:%d\n", lab_id, bomb_id, dest, v5, num_input_strings);
  v6 = 0;
  if ( num_input_strings > 0 )
  {
    do
    {
      v7 = v6 + 1;
      fprintf(v3, "bomb-string:%s:%d:%s:%d:%s\n", lab_id, bomb_id, dest, v6 + 1, (const char *)(80 * v6 + 134526592));
      v6 = v7;
    }
    while ( v7 < num_input_strings );
  }
  rewind(v3);
  sprintf(scratch, "%s %s@%s", "/usr/sbin/sendmail -bm", "bomb", "bluegill.cmcl.cs.cmu.edu");
  if ( system(scratch) )
  {
    printf("ERROR: notification error\n");
    exit(8);
  }
  if ( fclose(v3) )
  {
    printf("ERROR: fclose(tmp) error\n");
    exit(8);
  }
  if ( dup(v1) )
  {
    printf("ERROR: dup(tmpstdin) error\n");
    exit(8);
  }
  result = close(v1);
  if ( result )
  {
    printf("ERROR: close(tmpstdin)\n");
    exit(8);
  }
  return result;
}
// 80488C0: using guessed type int __cdecl cuserid(int);
// 804AE00: using guessed type int bomb_id;
// 804B480: using guessed type int num_input_strings;

//----- (080494FC) --------------------------------------------------------
void __noreturn explode_bomb()
{
  printf("\nBOOM!!!\n");
  printf("The bomb has blown up.\n");
  exit(8);
}

//----- (0804952C) --------------------------------------------------------
void phase_defused()
{
  char v0; // [esp+14h] [ebp-54h] BYREF
  char v1[80]; // [esp+18h] [ebp-50h] BYREF

  if ( num_input_strings == 6 )
  {
    if ( sscanf(s, "%d %s", &v0, v1) == 2 && !strings_not_equal(v1, "austinpowers") )
    {
      printf("Curses, you've found the secret phase!\n");
      printf("But finding it and solving it are quite different...\n");
      secret_phase();
    }
    printf("Congratulations! You've defused the bomb!\n");
  }
}