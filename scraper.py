'''
Web scraper that extracts information from: https://myanimelist.net/topanime.php and retrieves the names and scores of the top 50 anime.

'''
import requests

def main():
    scrap_nobeautifulsoup()


def scrap_nobeautifulsoup():
    scores_start1 = 'score-9">'
    scores_start2 = 'score-8">'
    end = '</'

    animes_start =  'alt="Anime: '
    animes_end = '" class='


    scores1 = std_scraper(scores_start1, end)  
    scores2 = std_scraper(scores_start2, end) 
    animes = std_scraper(animes_start, animes_end) 

    scores = []
    for score in scores1:
        scores.append(score)
    for score in scores2:
        scores.append(score)

    anime_list = []
    for anime in animes:
        anime_list.append(anime)

    dicio = {} 
    for i, anime in enumerate(anime_list):
        dicio[anime] = scores[i]

    for x, (anime, score) in enumerate(dicio.items(), start=1):
        print(f"Top {x}: {anime}, Score: {score}")


def std_scraper(start_marker, end_marker):
    url = 'https://myanimelist.net/topanime.php'
    response = requests.get(url)
    content = response.text
    
    start = 0
    marker = start_marker
    end_marker = end_marker

    data = []

    while True:
        start = content.find(marker, start)
        if start == -1:
            break

        start += len(marker)
        
        end = content.find(end_marker, start)
        if end == -1:
            break

        info = content[start:end]
        data.append(info)

        start = content.find(marker, end + len(end_marker))
    
    return data


main()