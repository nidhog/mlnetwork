import csv

filenames = ['Arabidopsis.csv',
            'Arxiv.csv',
            'multi_BA_BA.csv',
            'multi_ER_ER.csv',
            '']



def divide_layers(filename):
    print "[.] Processing file: "+ filename
    rows = {}
    last = 4
    with open(filename, 'rb') as f:
        reader = csv.reader(f)
        for row in reader:
            try:
                actor1, actor2, layer = row
                if (not(layer in rows.keys()) and len(rows.keys())<=3):
                    print "[..] New layer :"+str(layer)
                    rows[layer] =[] 
                if len(rows.keys())>3:
                    last = layer
                    break
                else:
                    rows[layer].append(([actor1, actor2]))
            except TypeError, e:
                print "[!] Could not process actors and layers"
                print e
    if last in rows:
        del rows[layer]
                
def main():
    for multilayer_file in filenames:
        divide_layers(multilayer_file)
        
if __name__=="__main__":
    main()
    
        
        
            
    
