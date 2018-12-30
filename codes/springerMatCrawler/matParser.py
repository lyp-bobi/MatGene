from html.parser import HTMLParser


class searchParser(HTMLParser):
    def __init__(self):
        HTMLParser.__init__(self)
        self.numOfResult = 0
        self.result = {}
        self.tmpValue = ""
        self.tmpValue2 = ""
        self.meetResult = False
        self.meetResult2 = False
        self.name1 = ""
        self.name2 = ""

    def handle_starttag(self, tag, attrs):
        if tag == 'a':
            if len(attrs) >= 3 and attrs[1] == ('class', "search_result"):
                self.tmpValue = attrs[3][1]
                self.meetResult = True
        if tag == 'li':
            if len(attrs) == 0:
                self.meetResult2 = True

    def handle_endtag(self, tag):
        if tag == 'a':
                self.meetResult = False
        if tag == 'li':
                self.meetResult2 = False

    def handle_data(self, data):
        if self.meetResult:
            self.meetResult = False
            self.name1 = str(data)
            self.name1 = self.name1.strip()
            self.name1 = self.name1.strip('\n')
            self.numOfResult += 1
        if self.meetResult2:
            self.meetResult2 = False
            self.name2 = str(data)
            self.name2 = self.name2.strip()
            self.name2 = self.name2.strip('\n')
            if self.name2.find("Temperature:")!=-1:
                name = self.name1 + ' ' + self.name2
                self.result[name] = self.tmpValue

class resultParser(HTMLParser):
    def __init__(self):
        HTMLParser.__init__(self)
        self.link = ""

    def handle_starttag(self, tag, attrs):
        if tag == 'img':
            if len(attrs) > 2 and attrs[0] == ('id', "phase_diagram_image"):
                self.link = "https://materials.springer.com" + attrs[1][1]
