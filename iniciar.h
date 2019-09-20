long long iniciar_x, iniciar_y, iniciar_z,iniciar_w;

void Seediniciar (){
  srand(time(NULL));
  time_t timer= time(NULL);
  struct tm y2k ;
  y2k.tm_hour = 0;
  y2k.tm_min = 0;
  y2k.tm_sec = 0;
  y2k.tm_year = 100;
  y2k.tm_mon = 0;
  y2k.tm_mday = 1;
  long long segundo= difftime(timer ,mktime(&y2k));//diferencia desde 1970
  iniciar_x = segundo;
  iniciar_y = segundo ^ 123456789;//operacion xor
  iniciar_z=segundo << 31;//shift left
  iniciar_w=segundo >> 11;//shift rigth
}

long long iniciar (long long MAX_XOR){
  long long tmp;
  tmp=iniciar_x ^( iniciar_x <<11);//xor
  iniciar_x=iniciar_y ;
  iniciar_y=iniciar_z ;
  iniciar_z=iniciar_w ;
  iniciar_w=iniciar_w ^ ( iniciar_w >>19)^(tmp^(tmp>>8)) ;//xor y shiftrigth
  return iniciar_w % MAX_XOR;//modulo
}
