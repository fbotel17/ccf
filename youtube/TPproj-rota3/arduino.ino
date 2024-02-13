void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
   
   int Index = 0;
}

void loop() {
  int i=0;
  // put your main code here, to run repeatedly:



float NOTE[50][2] = {
    {5050.0030, 0001.9930},     // Acheux-en-Amiénois
    {5049.8656, 0002.1036},     // Ailly-le-Haut-Clocher
    {5049.7895, 0002.3590},     // Airaines
    {5049.9922, 0002.0194},     // Arrest
    {5050.0982, 0001.6363},     // Béhen
    {5049.9095, 0002.1502},     // Boves
    {5049.9943, 0002.2516},     // Camon
    {5049.8547, 0002.1353},     // Corbie
    {5049.9528, 0002.1749},     // Dury
    {5049.9963, 0002.3923},     // Flixecourt
    {5049.8572, 0002.2287},     // Fouilloy
    {5049.9720, 0002.1104},     // Glisy
    {5050.0155, 0001.9435},     // Hangest-sur-Somme
    {5049.7649, 0002.4042},     // Hornoy-le-Bourg
    {5050.0575, 0002.0005},     // Longueau
    {5050.0835, 0001.7475},     // Noyelles-sur-Mer
    {5049.9805, 0002.1735},     // Poulainville
    {5050.0385, 0002.1295},     // Rivery
    {5050.1159, 0001.6906},     // Rue
    {5049.9355, 0002.3170},     // Saleux
    {5049.9547, 0002.3902},     // Salouël
    {5050.1495, 0001.5829},     // Saint-Riquier
    {5050.0182, 0002.2557},     // Vaux-sur-Somme
    {5050.0504, 0001.9388},     // Villers-Bretonneux
    {5049.9183, 0002.3785},     // Wiencourt-l'Équipée
    {5049.9314, 0002.1023},     // Moreuil
    {5049.9039, 0002.0726},     // Montdidier
    {5049.8790, 0002.0304},     // Rosières-en-Santerre
    {5049.8404, 0002.2548},     // Albert
    {5050.1512, 0002.0916},     // Doullens
    {5049.8583, 0002.3818},     // Acheux-en-Vimeu
    {5049.8190, 0002.4548},     // Friville-Escarbotin
    {5050.0063, 0002.0736},     // Candas
    {5049.9325, 0002.0483},     // Breteuil
    {5050.0095, 0001.9990},     // Méaulte
    {5049.9688, 0002.3838},     // Poix-de-Picardie
    {5049.8958, 0002.3483},     // Ailly-sur-Noye
    {5049.9683, 0002.3218},     // Berteaucourt-lès-Thennes
    {5050.0956, 0002.2075},     // Fressenneville
    {5050.0517, 0002.2320},     // Abbeville
    {5049.8480, 0002.0055},     // Bray-sur-Somme
    {5049.7813, 0002.3880},     // Gamaches
    {5049.9520, 0001.8748},     // Douilly
    {5050.0190, 0001.7895},     // Nouvion
    {5049.8446, 0002.1466},     // Villers-Bocage
    {5049.9970, 0002.2560},     // Querrieu
    {5050.1560, 0002.3666},     // Frévent
    {5050.0170, 0002.3752},     // Ailly-sur-Somme
    {5049.9210, 0002.2125},     // Cagny
    {5049.9148, 0002.2112},     // Bertangles
};


  
    for(i=0;i<50;i++){
      Serial.print("$GPGGA,084548,");
      //Latitude :
      Serial.print(NOTE[i][0],4);
      NOTE[i][0] = NOTE[i][0] + 1.1;
      Serial.print(",N,");
      //Longitude :
       Serial.print("00");
      Serial.print(NOTE[i][1],4);
      NOTE[i][1] = NOTE[i][1] + 1.3;
      Serial.println(",E,1,08,0.9,545.4,M,46.9,M, , *42");
      delay(1000);
    }
   
    
  
  
}
