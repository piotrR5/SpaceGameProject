TODO:
    grafika:
        wyswietlanie tla
        wyswietlanie obiektow
        debugowe wyswietlanie pól
    fizyka
        pola (podzielone na kwadraty) mogące wpływać na obiekty, zawierające jakieś parametry
        ruch i obrót obiektow
        statyczne obiekty wplywajace na pola
    logika
        obiekt mapa:
            tło
            pola:   vector<field>
                np grawitacja
                np magnetyzm
            obiekty statyczne: vector<static_object>
                np planety
            obiekty dynamiczne:    vector<dynamic_object>
                np statki
                np asteroidy
        obiekty dynamiczne:
            niesterowalne:     
                np asteroidy
                np rakieta 
            sterowalne:
                np statki
        obiekt sterowalny:
            vector<module>
        module:
            parametry rozne
        gun:
            parametry rozne
            
