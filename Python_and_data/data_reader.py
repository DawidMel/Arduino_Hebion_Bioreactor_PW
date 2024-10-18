import pandas as pd
import matplotlib.pyplot as plt

from os import getcwd, path
from matplotlib.dates import SecondLocator, MinuteLocator, DateFormatter
from tkinter import Tk, filedialog, Button


def generate_plot(filepath):
    
    sample_average:int = 10
    # Wczytujemy dane z pliku CSV
    df = pd.read_csv(filepath)

    # Obliczamy średnią kroczącą (moving average) z oknem sample_average
    df['temp_ma'] = df['temperatura'].rolling(window=sample_average).mean()
    df['ph_ma'] = df['ph'].rolling(window=sample_average).mean()
    df['stężenie_telnu_ma'] = df['stężenie_telnu'].rolling(window=sample_average).mean()


    # Konwertujemy kolumnę 'data' na typ datetime
    df['data'] = pd.to_datetime(df['data'], format='%H:%M:%S')

    first_data = df['data'].iloc[0]  

    last_data = df['data'].iloc[-1]

    difference = (last_data-first_data).total_seconds()//60

    if (difference<10):
        print("ZA KRÓTKIE OKNO OBSERWACJ!")
        difference = 10;

    point_interval:int = int(difference // 7) #od 7 do 14 punktów pomiarowych w granicy będzie ich 7

    print(f"difference: {difference}")


    # Tworzymy wykresy
    plt.figure(figsize=(10, 8))
    plt.gcf().canvas.manager.set_window_title('Mój Własny Tytuł Okna')

    # Wykres temperatury
    plt.subplot(3, 1, 1)
    plt.plot(df['data'], df['temp_ma'], linestyle='-')
    plt.title('Temperatura w czasie')
    plt.xlabel('Czas')
    plt.ylabel('Temperatura (°C)')

    plt.gca().xaxis.set_major_locator(MinuteLocator(interval=point_interval))  # Ustawia etykiety co 5 minut
    plt.gca().xaxis.set_major_formatter(DateFormatter('%H:%M'))  # Formatowanie do godziny i minut

    # Wykres pH
    plt.subplot(3, 1, 2)
    plt.plot(df['data'], df['ph_ma'], linestyle='-')
    plt.title('pH w czasie')
    plt.xlabel('Czas')
    plt.ylabel('pH')

    plt.gca().xaxis.set_major_locator(MinuteLocator(interval=point_interval))  # Ustawia etykiety co 5 minut
    plt.gca().xaxis.set_major_formatter(DateFormatter('%H:%M'))  # Formatowanie do godziny i minut

    # Wykres stężenia tlenu
    plt.subplot(3, 1, 3)
    plt.plot(df['data'], df['stężenie_telnu_ma'], linestyle='-')
    plt.title('Stężenie tlenu w czasie')
    plt.xlabel('Czas')
    plt.ylabel('Stężenie tlenu (mg/L)')

    plt.gca().xaxis.set_major_locator(MinuteLocator(interval=point_interval))  # Ustawia etykiety co 5 minut
    plt.gca().xaxis.set_major_formatter(DateFormatter('%H:%M'))  # Formatowanie do godziny i minut

    # Dostosowujemy układ wykresów
    plt.tight_layout()

    # Wyświetlamy wykresy
    plt.show()



def open_file():
    filepath = filedialog.askopenfilename(initialdir=getcwd()+"/Python_and_data",
                                            title="wybierz plik",
                                            filetypes=[("CSV files", "*.csv")]
                                        )


    generate_plot(filepath)
    print("odczytano plik: " +  path.basename(filepath))


window = Tk()
button = Button(text="otwórz wykres",command=open_file)
button.pack()
window.mainloop()





#pick folder using user file search

