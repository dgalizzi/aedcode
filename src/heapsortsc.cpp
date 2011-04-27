// Fase inicial
// Pone todos los elementos en S  
while (!L.empty()) {
  x = *L.begin();
  S.insert(x);
  L.erase(L.begin());
}
// Fase final
// Saca los elementos de S usando `min' 
while (!S.empty()) {
  x = *S.begin();
  S.erase(S.begin());
  L.push(L.end(),x);
