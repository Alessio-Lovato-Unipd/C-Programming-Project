#!/bin/bash

directory_attuale=$(dirname -- $(readlink -fn -- "$0"))
test="${directory_attuale}/build"

# OPZIONE PER SEEZIONARE L'UTILIZZO DI VALGRIND NEI TEST
ANALISI_MEMORIA=true

echo
echo "Eliminazione cartella build"
echo "Assicurarsi che il file CMakeLists.txt sia configurato per il gruppo 'test'"
echo
echo "Si hanno 10 secondi per uscire dal programma premendo CTRL+C"
echo
sleep 10

rm -r $test
#creazione cartella per il testing
mkdir $test
cd $test
cmake ..
make
echo
echo "Avvio testing in versione normale"
echo
sleep 1

#TEST CSV
echo "Test CSV"
echo
sleep 2
cd $test/test/test_csv/
if [ "$ANALISI_MEMORIA" = false ]
then
    ./test2
else
    valgrind ./test2
fi
#pausa per controllare i risultati
echo


sleep 3



#TEST ESTRATTORE TURBINE
echo
echo "Test ESTRATTORE TURBINE"
echo
sleep 2
cd $test/test/test_estrazione/
if [ "$ANALISI_MEMORIA" = false ]
then
    ./test_estrazione_turbine
else
    valgrind ./test_estrazione_turbine
fi
#pausa per controllare i risultati
sleep 3

#TEST ESTRATTORE WEATHER
echo
echo "Test ESTRATTORE WEATHER"
echo
sleep 2
cd $test/test/test_estrazione/
if [ "$ANALISI_MEMORIA" = false ]
then
    ./test_estrazione_weather
else
    valgrind ./test_estrazione_weather
fi
#pausa per controllare i risultati
sleep 3

#TEST ESTRATTORE CURVE
echo
echo "Test ESTRATTORE CURVE"
echo
sleep 2
cd $test/test/test_estrazione/
if [ "$ANALISI_MEMORIA" = false ]
then
    ./test_estrazione_curve
else
    valgrind ./test_estrazione_curve
fi
#pausa per controllare i risultati
sleep 3


#TEST CALCOLO OUTPUT
echo
echo "Test CALCOLO OUTPUT"
echo
sleep 2
cd $test/test/test_calcolo_output/
if [ "$ANALISI_MEMORIA" = false ]
then
    ./test_calcolo_output
else
    valgrind ./test_calcolo_output
fi
#pausa per controllare i risultati
sleep 3


#TEST FORMULE
echo
echo "Test FORMULE"
echo
sleep 2
cd $test/test/test_formule/
if [ "$ANALISI_MEMORIA" = false ]
then
    ./test_formule
else
    valgrind ./test_formule
fi
#pausa per controllare i risultati
sleep 3

#TEST PARAMETRI
echo
echo "Test PARAMETRI"
echo
sleep 2
cd $test/test/test_parametri/
if [ "$ANALISI_MEMORIA" = false ]
then
    ./test_parametri
else
    valgrind ./test_parametri
fi
#pausa per controllare i risultati
sleep 3


#TEST PLOT
echo
echo "Test PLOT"
echo
sleep 2
cd $test/test/test_plot/
if [ "$ANALISI_MEMORIA" = false ]
then
    ./test_plot
else
    valgrind ./test_plot
fi
#pausa per controllare i risultati
sleep 3


##############################################################
# TESTING IN VERSIONE RELEASE

SUCCESSO=true

cd $directory_attuale
rm -r $test
#creazione cartella per il testing
mkdir $test
cd $test
cmake -DCMAKE_BUILD_TYPE=Release ..
make
echo
echo "Avvio testing in versione release"
echo
sleep 3

#TEST CSV
echo "Test CSV"
echo
sleep 2
cd $test/test/test_csv/
if [ "$ANALISI_MEMORIA" = false ]
then
    ./test2
else
    valgrind ./test2
fi
#pausa per controllare i risultati
echo


sleep 3



#TEST ESTRATTORE TURBINE
echo
echo "Test ESTRATTORE TURBINE"
echo
sleep 2
cd $test/test/test_estrazione/
if [ "$ANALISI_MEMORIA" = false ]
then
    ./test_estrazione_turbine
else
    valgrind ./test_estrazione_turbine
fi
#pausa per controllare i risultati
sleep 3

#TEST ESTRATTORE WEATHER
echo
echo "Test ESTRATTORE WEATHER"
echo
sleep 2
cd $test/test/test_estrazione/
if [ "$ANALISI_MEMORIA" = false ]
then
    ./test_estrazione_weather
else
    valgrind ./test_estrazione_weather
fi
#pausa per controllare i risultati
sleep 3

#TEST ESTRATTORE CURVE
echo
echo "Test ESTRATTORE CURVE"
echo
sleep 2
cd $test/test/test_estrazione/
if [ "$ANALISI_MEMORIA" = false ]
then
    ./test_estrazione_curve
else
    valgrind ./test_estrazione_curve
fi
#pausa per controllare i risultati
sleep 3


#TEST CALCOLO OUTPUT
echo
echo "Test CALCOLO OUTPUT"
echo
sleep 2
cd $test/test/test_calcolo_output/
if [ "$ANALISI_MEMORIA" = false ]
then
    ./test_calcolo_output
else
    valgrind ./test_calcolo_output
fi
#pausa per controllare i risultati
sleep 3


#TEST FORMULE
echo
echo "Test FORMULE"
echo
sleep 2
cd $test/test/test_formule/
if [ "$ANALISI_MEMORIA" = false ]
then
    ./test_formule
else
    valgrind ./test_formule
fi
#pausa per controllare i risultati
sleep 3

#TEST PARAMETRI
echo
echo "Test PARAMETRI"
echo
sleep 2
cd $test/test/test_parametri/
if [ "$ANALISI_MEMORIA" = false ]
then
    ./test_parametri
else
    valgrind ./test_parametri
fi
#pausa per controllare i risultati
sleep 3


#TEST PLOT
echo
echo "Test PLOT"
echo
sleep 2
cd $test/test/test_plot/
if [ "$ANALISI_MEMORIA" = false ]
then
    ./test_plot
else
    valgrind ./test_plot
fi

echo
