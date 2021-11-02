void CamadaEnlaceDadosTransmissora(int quadro [], int size);

int* CamadaEnlaceDadosTransmissoraEnquadramento(int quadro [], int size);

void CamadaEnlaceDadosTransmissoraControleDeErro(int quadro [], int size);

int* CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(int quadro [], int size);

int* CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(int quadro [], int size);

void CamadaEnlaceDadosReceptora(int quadroEnquadrado [], int size);

int* CamadaEnlaceDadosReceptoraEnquadramento(int quadroEnquadrado[], int size);

void CamadaEnlaceDadosReceptoraControleDeErro(int quadro [], int size);

void CamadaEnlaceDadosReceptora(int quadro []);

int* CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(int quadroEnquadrado []);

int* CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(int quadroEnquadrado [], int size);

int* CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(int quadro[], int size);

void CamadaEnlaceDadosTransmissoraControleDeErroCRC(int quadro[], int size);

void CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(int quadro[], int size);

void CamadaEnlaceDadosReceptoraControleDeErroCRC(int quadro[], int size);