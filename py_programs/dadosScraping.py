import requests
from bs4 import BeautifulSoup # pip install beautifulsoup4

def fazer_scraping():

    url = input("Digite o link do site que deseja fazer scraping: ")
    response = requests.get(url)

    if response.status_code == 200:
        soup = BeautifulSoup(response.text, 'html.parser')

        links = soup.find_all('a', href=True)
        print("Links encontrados na página:")
        for link in links:
            print(link['href'])

        imagens = soup.find_all('img', src=True)
        print("\nImagens encontradas na página:")
        for imagem in imagens:
            print(imagem['src'])

        paragrafos = soup.find_all('p')
        print("\nParágrafos encontrados na página:")
        for paragrafo in paragrafos:
            print(paragrafo.text.strip())

        with open('dados_scraping.txt', 'w', encoding='utf-8') as file:

            file.write("Links encontrados na página:\n")
            for link in links:
                file.write(link['href'] + '\n')

            file.write("\nImagens encontradas na página:\n")
            for imagem in imagens:
                file.write(imagem['src'] + '\n')

            file.write("\nParágrafos encontrados na página:\n")
            for paragrafo in paragrafos:
                file.write(paragrafo.text.strip() + '\n')

        print("\nDados de scraping foram armazenados com sucesso.")
    else:
        print("Falha ao acessar a página.")

if __name__ == "__main__":
    fazer_scraping()
