# SudoPassExamLII2122
Repository per progetto turbine eoliche LII2122


Per eseguire in maniera automatica i test è sufficiente, nella cartella principale, assicurarsi che il CMakeLists.txt sia impostato nel gruppo "test" 
ed eseguire nella CLI questo comando:

bash test.sh

Il test viene eseguito sia nella versione dei file compilati normalmente, che in versione Release.
Per eseguire i test di memoria inizializzare la variabile "ANALISI_MEMORIA" con valore true.