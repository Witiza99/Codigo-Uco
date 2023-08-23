@Ejemplo de los operadores numéricos

writestring('Introduce el primer operador: \n');
read(op1);

writestring('Introduce el segundo operador: \n');
read(op2);

@Operadores binarios
res := op1 + op2;

writestring('el resultado de ');
write(op1);
writestring(' + ');
write(op2);
writestring(' es: \n');
write(res);
writestring('\n');


res := op1 - op2;

writestring('el resultado de ');
write(op1);
writestring(' - ');
write(op2);
writestring(' es: \n');
write(res);
writestring('\n');


res := op1 * op2;

writestring('el resultado de ');
write(op1);
writestring(' * ');
write(op2);
writestring(' es: \n');
write(res);
writestring('\n');


res := op1 / op2;

writestring('el resultado de ');
write(op1);
writestring(' / ');
write(op2);
writestring(' es: \n');
write(res);
writestring('\n');


res := op1 quotient op2;

writestring('el resultado de la division entera ');
write(op1);
writestring(' quotient ');
write(op2);
writestring(' es: \n');
write(res);
writestring('\n');


res := op1 modulo op2;

writestring('el modulo de ');
write(op1);
writestring(' modulo ');
write(op2);
writestring(' es: \n');
write(res);
writestring('\n');


res := op1 ** op2;

writestring('el resultado de ');
write(op1);
writestring(' elevado a ');
write(op2);
writestring(' es: \n');
write(res);
writestring('\n');

@Operadores unarios
res := +op1;
writestring(' +');
write(op1);
writestring(' es igual a ');
write(res);
writestring('\n');

res := -op1;
writestring(' -');
write(op1);
writestring(' es igual a ');
write(res);
writestring('\n');
