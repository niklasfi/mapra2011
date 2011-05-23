
// ----- Maximum-Norm -----

double Matrix::NormMax() const
{
    // ***** Hier fehlt was *****
	
	double zsum;
	double zsummax = 0;
	
	for(int i = 0; i < Zeil; i++){
		zsum = 0;
	
		for (int j = 0; j < Spalt; j++)
			zsum += fabs((*this)(i,j));			// Summieren der Zeileneintraeger einzeln zum Betrag
		
		if (zsummax < zsum) zsummax = zsum;
	}
	
	return zsummax;
}

