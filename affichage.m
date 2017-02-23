%%%%Ouverture%%%
fileID = fopen('obstacles', 'r') ;

%%%Lecture de l'ensemble des sommets%%%
c = textscan(fileID,'%f%c%f','Delimiter',{';'}); % c{1} : liste des x des sommets /c{3} : liste des y
celldisp(c) ;
sommetsX = c{1};
sommetsY = c{3};

%%%Lecture et affichage des obstacles un par un (0K)%%%
frewind(fileID); %On revient au début du fichier
ligne = fgetl(fileID); 
hold on ;
while ischar(ligne)
    c = textscan(ligne, '%f%c%f','Delimiter',{';'});
    celldisp(c) ;
    %Affichage de l'obstacle
    c{1}= cat(1,c{1},c{1}(1));
    c{3} = cat(1,c{3},c{3}(1));
    plot(c{1},c{3});
    ligne = fgetl(fileID) 
end


%%%Fermeture%%%
fclose(fileID);
