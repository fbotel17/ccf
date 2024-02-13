

<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Documentation de la classe Compteur_Histo</title>

  <style>
    body {
      font-family: Arial, sans-serif;
      line-height: 1.6;
      margin: 20px;
    }

    header {
      background-color: #f2f2f2;
      padding: 10px;
      border-radius: 5px;
      margin-bottom: 20px;
    }

    section {
      margin-bottom: 30px;
    }

    h2 {
      color: #1a73e8;
    }

    h3 {
      color: #4caf50;
    }

    ul {
      list-style-type: none;
      padding: 0;
    }

    pre {
      background-color: #f5f5f5;
      padding: 10px;
      border-radius: 5px;
    }
  </style>
</head>
<body>

  <header>
    <h1>Documentation de la classe Compteur_Histo</h1>

  </header>

  <section>
    <h2>Constructeur</h2>
    <article>
        <h3>Description</h3>
        <p>Constructeur de la classe Compteur_Histo.</p>

        <h3>Paramètres</h3>
        <ul>
            <li><code>apiKey1</code>: AIzaSyAmTs9KwHabkrc65xzdXbaMN7Wnkm_io44</li>
            <li><code>apiKey2</code>: AIzaSyCLhJz_RWKVRHElQOFUailof1vSBzw7Ylo</li>
            <li><code>channelId</code>: UCXH88XOJR72jvzglmLIOleQ</li>
        </ul>

        <h3>Utilisation</h3>
        <div id="resultat"></div>
      <pre>  <code> if (compteurhisto === null) {
                document.getElementById("resultat").innerHTML = "KO";
            } else {
                document.getElementById("resultat").innerHTML = "OK";
            }</code></pre>
        <script type="module">
            // Importez la classe depuis le fichier externe
            import Compteur_Histo from './Classes/Compteur_Histo.js';

            // Informations concernant l'API
            const apiKey1 = "AIzaSyAmTs9KwHabkrc65xzdXbaMN7Wnkm_io44";
            const apiKey2 = "AIzaSyCLhJz_RWKVRHElQOFUailof1vSBzw7Ylo";
            const channelId = "UCXH88XOJR72jvzglmLIOleQ"; // ID : Douzzy Abozo

            // Création d'une instance de la classe Compteur_Histo. Cette classe gère tout le compteur d'abonnée youtube
            let compteurhisto = new Compteur_Histo(apiKey1, apiKey2, channelId);

            // Vérification et affichage du résultat sur la page
            if (compteurhisto === null) {
                document.getElementById("resultat").innerHTML = "KO";
            } else {
                document.getElementById("resultat").innerHTML = "OK";
            }
        </script>
    </article>
</section>


<section>
    <h2>Méthode <code>getNbRequetesFromBack()</code></h2>
    <article>
        <h3>Description</h3>
        <p>Récupère le nombre de requêtes actuel en BDD du back.</p>

        <h3>Utilisation</h3>
        <pre>
            <code>
            async function getNbRequetesFromBack() {
                const resultContainer = document.getElementById('resultContainer');

                try {
                    const response = await fetch('http://192.168.65.237:8080/new/Classes/Compteur_Histo/PostNBRequetes', {
                        method: 'POST',
                        headers: {
                            'Content-Type': 'application/json',
                        },
                        body: JSON.stringify({}),
                    });

                    const data = await response.json();
                    resultContainer.innerHTML = 'OK ! Nombre de requêtes en BDD : ' + data.nbrequetes;
                    return data.nbrequetes;
                } catch (error) {
                    resultContainer.innerHTML = 'KO ! Erreur lors de la récupération du nombre de requêtes depuis le serveur : ' + error;
                    throw error;
                }
            }

            getNbRequetesFromBack();
            </code>
        </pre>
        <div id="resultContainer"></div>

        <script type="module">
            async function getNbRequetesFromBack() {
                const resultContainer = document.getElementById('resultContainer');

                try {
                    const response = await fetch('http://192.168.65.237:8080/new/Classes/Compteur_Histo/PostNBRequetes', {
                        method: 'POST',
                        headers: {
                            'Content-Type': 'application/json',
                        },
                        body: JSON.stringify({}),
                    });

                    const data = await response.json();
                    resultContainer.innerHTML = 'OK ! Nombre de requêtes en BDD : ' + data.nbrequetes;
                    return data.nbrequetes;
                } catch (error) {
                    resultContainer.innerHTML = 'KO ! Erreur lors de la récupération du nombre de requêtes depuis le serveur : ' + error;
                    throw error;
                }
            }

            getNbRequetesFromBack();
        </script>
    </article>
</section>



<section>

    <h2>Méthode <code>getDateFromBack()</code></h2>
    <article>
        <h3>Description</h3>
        <p>Récupère la date de la dernière entrée en BDD du back.</p>

        <h3>Utilisation</h3>
        <pre>
            <code>
            async function getDateFromBack() {
                try {
                    const response = await fetch('http://192.168.65.237:8080/new/Classes/Compteur_Histo/PostDate', {
                        method: 'POST',
                        headers: {
                            'Content-Type': 'application/json',
                        },
                        body: JSON.stringify({}),
                    });

                    let data = await response.json();
                    console.log('Jour de la dernière entrée en BDD : ', data.number); // Ajout de ce log

                    return data.number;
                } catch (error) {
                    console.error('Erreur lors de la récupération du nombre de requêtes depuis le serveur :', error);
                    throw error;
                }
            }

            getDateFromBack();
            </code>
        </pre>
        <div id="dateResultContainer"></div>
        <script type="module">
              async function getDateFromBack() {
        try {
            const response = await fetch('http://192.168.65.237:8080/new/Classes/Compteur_Histo/PostDate', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({}),
            });

            let data = await response.json();
            dateResultContainer.innerHTML = 'OK ! Jour de la dernière entrée en BDD : '  + data.number; // Ajout de ce log

            return data.number;
        } catch (error) {
          dateResultContainer.innerHTML = 'KO ! Erreur lors de la récupération du nombre de requêtes depuis le serveur :', error;
            throw error;
        }
    }
    getDateFromBack(); </script>
    </article>
</section>

<section>
    <h2>Fonction <code>sendInfoToCpp(info)</code></h2>
    <article>
        <h3>Description</h3>
        <p>Envoie des informations au serveur via WebSocket.</p>

        <h3>Utilisation</h3>
        <pre>
            <code>
                function sendInfoToCpp(info) {
                    // Vérifier si la connexion WebSocket est ouverte
                    if (this.socket.readyState === WebSocket.OPEN) {
                        this.socket.send(info);
                        resultContainer.innerHTML = 'OK ! Info envoyée avec succès : ' + info;
                    } else {
                        resultContainer.innerHTML = 'KO ! La connexion WebSocket n\'est pas ouverte.';
                    }
                }

                // Utilisation de la fonction sendInfoToCpp
                const infoToSend = 'Votre information ici';
                sendInfoToCpp(infoToSend);
            </code>
        </pre>
        <div id="ohohresultContainer"></div>
        <script type="module">
    const socket = new WebSocket('ws://192.168.65.61:667');

    // Définir le message par défaut à "KO"
    document.getElementById('ohohresultContainer').innerHTML = 'KO ! Test ECHOUE : lalalala';

    // Écouter l'événement d'ouverture de la connexion WebSocket
    socket.addEventListener('open', (event) => {
        // Changer le message en "OK" lorsque la connexion est ouverte
        document.getElementById('ohohresultContainer').innerHTML = 'OK ! Test réussi : lalalala';
    });

    function sendInfoToCpp(info) {
        if (socket.readyState === WebSocket.OPEN) {
            socket.send(info);
        }
        // Vous pouvez également gérer le cas où la connexion n'est pas ouverte ici
    }
</script>
    </article>
    <section>
    <h2>Fonction <code>getChannelInfo()</code></h2>
    <article>
        <h3>Description</h3>
        <p>Récupère les informations d'une chaîne YouTube en utilisant son identifiant.</p>

        <h3>Test Unitaire</h3>
        <pre><code>
            document.addEventListener("DOMContentLoaded", function () {
                // Remplacez YOUR_API_KEY par l'API key fournie
                var apiKey = "AIzaSyAmTs9KwHabkrc65xzdXbaMN7Wnkm_io44";
                // Remplacez CHANNEL_ID par l'ID de votre chaîne YouTube
                var channelId = "UCXH88XOJR72jvzglmLIOleQ";

                var apiUrl = `https://www.googleapis.com/youtube/v3/channels?part=snippet,statistics&id=${channelId}&key=${apiKey}`;

                var channelinfocontainer = document.getElementById("channelinfocontainer");

                // Effectuez la demande API YouTube
                fetch(apiUrl)
                    .then(response => {
                        if (!response.ok) {
                            throw new Error('La requête API a échoué.');
                        }
                        return response.json();
                    })
                    .then(data => {
                        // Manipulez les données de la réponse ici
                        displayChannelInfo(data);
                        displayResultMessage("OK !");
                    })
                    .catch(error => {
                        console.error('Erreur lors de la requête API YouTube:', error);
                        displayResultMessage(`KO ! Erreur : ${error.message}`);
                    });
            });

            function displayChannelInfo(data) {
                var channelinfocontainer = document.getElementById("channelinfocontainer");
                var channelData = data.items[0];

                var channelTitle = channelData.snippet.title;
                var channelSubscribers = channelData.statistics.subscriberCount;

                // Affichez le nom de la chaîne et le nombre d'abonnés dans le conteneur de résultats
                channelinfocontainer.innerHTML += `
                    <p>Nom de la chaîne: ${channelTitle}</p>
                    <p>Nombre d'abonnés: ${channelSubscribers}</p>
                `;
            }

            function displayResultMessage(message) {
                var channelinfocontainer = document.getElementById("channelinfocontainer");
                channelinfocontainer.innerHTML += `<p>${message}</p>`;
            }
        </code></pre>
        <div id="channelinfocontainer"></div>
<script type="module">
    document.addEventListener("DOMContentLoaded", function () {
        // Remplacez YOUR_API_KEY par l'API key fournie
        var apiKey = "AIzaSyAmTs9KwHabkrc65xzdXbaMN7Wnkm_io44";
        // Remplacez CHANNEL_ID par l'ID de votre chaîne YouTube
        var channelId = "UCXH88XOJR72jvzglmLIOleQ";

        var apiUrl = `https://www.googleapis.com/youtube/v3/channels?part=snippet,statistics&id=${channelId}&key=${apiKey}`;

        var channelinfocontainer = document.getElementById("channelinfocontainer");

        // Effectuez la demande API YouTube
        fetch(apiUrl)
            .then(response => {
                if (!response.ok) {
                    throw new Error('La requête API a échoué.');
                }
                return response.json();
            })
            .then(data => {
                // Manipulez les données de la réponse ici
                displayChannelInfo(data);
                displayResultMessage("OK !");
            })
            .catch(error => {
                console.error('Erreur lors de la requête API YouTube:', error);
                displayResultMessage(`KO ! Erreur : ${error.message}`);
            });
    });

    function displayChannelInfo(data) {
        var channelinfocontainer = document.getElementById("channelinfocontainer");
        var channelData = data.items[0];

        var channelTitle = channelData.snippet.title;
        var channelSubscribers = channelData.statistics.subscriberCount;

        // Affichez le nom de la chaîne et le nombre d'abonnés dans le conteneur de résultats
        channelinfocontainer.innerHTML += `
            <p>Nom de la chaîne: ${channelTitle}</p>
            <p>Nombre d'abonnés: ${channelSubscribers}</p>
        `;
    }

    function displayResultMessage(message) {
        var channelinfocontainer = document.getElementById("channelinfocontainer");
        channelinfocontainer.innerHTML += `<p>${message}</p>`;
    }
</script>
    </article>
</section>

</body>
</html>


  <section>
    <h2>Méthode <code>PostToBack()</code></h2>
    <article>
      <h3>Description</h3>
      <p>Envoie les données du front au back en vérifiant qu'elles sont bien définies.</p>

      <h3>Utilisation</h3>
      <pre>
        <code>
          compteur.PostToBack();
        </code>
      </pre>
      <div id="testResult"></div>
      <script type="module">
            function PostToBack() {
                const waitForVariables = async () => {
                    return new Promise((resolve, reject) => {
                        const checkVariables = () => {
                            if (this.channelName !== undefined && this.subscriberCount !== undefined) {
                                resolve();
                            } else {
                                setTimeout(checkVariables, 100);
                            }
                        };
                        checkVariables();
                    });
                };

                waitForVariables().then(() => {
                    const dataToSend = {
                        channelName: this.channelName,
                        subscriberCount: Number(this.subscriberCount),
                        // ... autres données
                    };

                    // Affichez les données envoyées dans la div de résultats
                    document.getElementById('testResult').innerHTML += '<p>Données envoyées : ' + JSON.stringify(dataToSend) + '</p>';

                    fetch('http://192.168.65.237:8080/new/Classes/Compteur_Histo', {
                        method: 'POST',
                        headers: {
                            'Content-Type': 'application/json',
                        },
                        body: JSON.stringify(dataToSend),
                    })
                        .then(response => {
                            if (!response.ok) {
                                throw new Error('La requête a échoué avec le statut ' + response.status);
                            }
                            return response.json();
                        })
                        .then(data => {
                            // Affichez la réponse du serveur dans la div de résultats
                            document.getElementById('testResult').innerHTML += '<p>Réponse du serveur : ' + JSON.stringify(data) + '</p>';
                            document.getElementById('testResult').innerHTML += '<p>OK !</p>';
                        })
                        .catch(error => {
                            // Affichez l'erreur dans la div de résultats
                            document.getElementById('testResult').innerHTML += '<p>Erreur lors de la requête POST : ' + error.message + '</p>';
                            document.getElementById('testResult').innerHTML += '<p>KO !</p>';
                        });
                });
            }

            // Exécutez la fonction PostToBack
            PostToBack.call({
                channelName: 'TestChannel',
                subscriberCount: 100,
                // ... autres données nécessaires
            });
        </script>
</article>


</body>
</html>
