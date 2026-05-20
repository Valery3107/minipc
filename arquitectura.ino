/*
 * Luvian OS v5.0 - ESP32 DevKit
 * ILI9341 320x240 SPI, XPT2046 Touch, SD Card, DHT11, Buzzer, LED
 * MEJORAS v5.1 - Seccion de Juegos Optimizada
 */

#include <SPI.h>
#include <SD.h>
#include <Adafruit_ILI9341.h>
#include <XPT2046_Touchscreen.h>
#include <DHT.h>

#define PIN_TFT_CS      15
#define PIN_TFT_DC       2
#define PIN_TFT_RST      4
#define PIN_TOUCH_CS    21
#define PIN_TOUCH_IRQ   22
#define PIN_SD_CS        5
#define PIN_BUZZER      27
#define PIN_DHT         16

#define TIPO_DHT        DHT11
DHT dht(PIN_DHT, TIPO_DHT);

#define TS_MINX         300
#define TS_MAXX         3700
#define TS_MINY         300
#define TS_MAXY         3700

#define ANCHO_PANTALLA  320
#define ALTO_PANTALLA   240

#define C_FONDO_PRINCIPAL     0x10A2
#define C_FONDO_SECUNDARIO    0x18C3
#define C_FONDO_TERCIARIO     0x2104
#define C_FONDO_ACENTO        0x2945

#define C_MARCA_PRIMARIO      0x5D7C
#define C_MARCA_CLARO         0x7FFF
#define C_MARCA_OSCURO        0x3D5C
#define C_MARCA_BRILLO        0x6E9C

#define C_TEXTO_PRINCIPAL     0xE73C
#define C_TEXTO_SECUNDARIO    0xB596
#define C_TEXTO_TERCIARIO     0x8C51
#define C_TEXTO_MARCA         0x5D7C
#define C_TEXTO_INVERTIDO     0x0000

#define C_EXITO               0x3666
#define C_ADVERTENCIA         0xFE20
#define C_ERROR               0xD8A0
#define C_INFO                0x2D7F

#define C_BORDE               0x2945
#define C_BORDE_ACTIVO        0x5D7C
#define C_BOTON_INACTIVO      0x18C3
#define C_BOTON_HOVER         0x2104
#define C_BOTON_PRESIONADO    0x3D5C
#define C_DIVISOR             0x2104
#define C_PANEL_FONDO         0x18C3
#define C_PANEL_BORDE         0x2945

#define C_ICON_FOLDER    0xFE20
#define C_ICON_CHIP      0x5D7C
#define C_ICON_THERMO    0xD8A0
#define C_ICON_GAMEPAD   0x07E0
#define C_ICON_CALC      0xE73C
#define C_ICON_CLOCK     0x2D7F
#define C_ICON_BRUSH     0xF81F
#define C_ICON_GEAR      0x8C51

#define BOOT_BAR_X       40
#define BOOT_BAR_Y       155
#define BOOT_BAR_W       240
#define BOOT_BAR_H       10


#define C_TOAST_FONDO         0x2945
#define C_TOAST_EXITO         0x3666
#define C_TOAST_ERROR         0xD8A0
#define C_TOAST_INFO          0x2D7F

#define C_PONG_FONDO          0x0841
#define C_PONG_CAMPO          0x0C63
#define C_PONG_PALETA_J       0x5D7C
#define C_PONG_PALETA_CPU     0xD8A0
#define C_PONG_BOLA           0xE73C
#define C_PONG_BOLA_RASTRO    0x7FFF
#define C_PONG_MARCADOR       0x5D7C
#define C_PONG_LINEA          0x18C3

#define C_SI_NAVE             0x5D7C
#define C_SI_NAVE_MOTOR       0x7FFF
#define C_SI_ALIEN1           0xFE20
#define C_SI_ALIEN2           0xD8A0
#define C_SI_ALIEN3           0x07E0
#define C_SI_BALA             0xE73C
#define C_SI_EXPLOSION        0xD8A0
#define C_SI_ESTRELLA         0x8C51

#define C_PAINT_FONDO         0xFFFF
#define C_PAINT_GRID          0x8410

#define ENCABEZADO_ALTO       32
#define ENCABEZADO_Y          0

#define BTN_FILA1_Y           42
#define BTN_FILA1_ALTO        52
#define BTN_ANCHO             100
#define BTN_ALTO              52
#define BTN_COL1_X            5
#define BTN_COL2_X            110
#define BTN_COL3_X            215
#define BTN_FILA2_Y           100
#define BTN_FILA3_Y           158

#define BTN_JUEGO_ANCHO       140
#define BTN_JUEGO_ALTO        70
#define BTN_JUEGO_Y           85
#define BTN_PONG_X            15
#define BTN_SPACE_X           165

#define BTN_VOLVER_X          10
#define BTN_VOLVER_Y          200
#define BTN_VOLVER_ANCHO      300
#define BTN_VOLVER_ALTO       32

#define BTN_NOTAS_X           10
#define BTN_NOTAS_Y           150
#define BTN_NOTAS_ANCHO       140
#define BTN_NOTAS_ALTO        28

#define CALC_BTN_ANCHO        70
#define CALC_BTN_ALTO         32
#define CALC_BTN_FILA1_Y      88
#define CALC_BTN_FILA2_Y      124
#define CALC_BTN_FILA3_Y      160
#define CALC_BTN_FILA4_Y      196
#define CALC_COL1_X           10
#define CALC_COL2_X           88
#define CALC_COL3_X           166
#define CALC_COL4_X           244
#define CALC_DISPLAY_Y        38
#define CALC_DISPLAY_ALTO     42
#define CALC_DISPLAY_X        10
#define CALC_DISPLAY_W        300
#define CALC_DISPLAY_PAD_R    15
#define CALC_BTN_CERRAR_X     280
#define CALC_BTN_CERRAR_Y     2
#define CALC_BTN_CERRAR_W     36
#define CALC_BTN_CERRAR_H     28

#define BTN_VOLVER_U_X      2
#define BTN_VOLVER_U_Y      2
#define BTN_VOLVER_U_W      58
#define BTN_VOLVER_U_H      28

#define BTN_PAINT_LIMPIAR_X 180
#define BTN_PAINT_LIMPIAR_Y 2
#define BTN_PAINT_LIMPIAR_W 64
#define BTN_PAINT_LIMPIAR_H 28

#define BTN_PAINT_GUARDAR_X 248
#define BTN_PAINT_GUARDAR_Y 2
#define BTN_PAINT_GUARDAR_W 64
#define BTN_PAINT_GUARDAR_H 28

#define PONG_PALETA_ANCHO     8
#define PONG_PALETA_ALTO      50
#define PONG_BOLA_RADIO       4
#define PONG_BOLA_DIAM        (PONG_BOLA_RADIO * 2)
#define PONG_FPS_MS           16
#define PONG_VEL_CPU          5
#define PONG_VEL_BOLA         3
#define PONG_PUNTOS_VICTORIA  5
#define PONG_MARGEN           4

#define PONG_AREA_X           PONG_MARGEN
#define PONG_AREA_Y           35
#define PONG_AREA_ANCHO       (ANCHO_PANTALLA - PONG_MARGEN * 2)
#define PONG_AREA_ALTO        (ALTO_PANTALLA - PONG_AREA_Y - PONG_MARGEN)
#define PONG_PALETA_J_X       (PONG_AREA_X + 6)
#define PONG_PALETA_CPU_X     (PONG_AREA_X + PONG_AREA_ANCHO - PONG_PALETA_ANCHO - 6)

#define SI_FILAS              3
#define SI_COLUMNAS           6
#define SI_ALIEN_ANCHO        18
#define SI_ALIEN_ALTO         12
#define SI_NAVE_ANCHO         20
#define SI_NAVE_ALTO          12

#define SCREENSAVER_TIMEOUT   60000
#define MAX_TOASTS            3
#define MAX_RUTA_SD           128
#define MAX_NOMBRE_ARCHIVO    32


// === ICONOS 24x24 PARA MENU PRINCIPAL ===
const uint8_t ICON_FOLDER[72] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x07, 0xFE, 0x00, 0x0F, 0xFF, 0x00, 0x0F, 0xFF, 0xF0, 0x0F, 0xFF, 0xF0,
  0x0F, 0xFF, 0xF0, 0x0F, 0xFF, 0xF0, 0x0F, 0xFF, 0xF0, 0x0F, 0xFF, 0xF0,
  0x0F, 0xFF, 0xF0, 0x0F, 0xFF, 0xF0, 0x07, 0xFF, 0xE0, 0x07, 0xFF, 0xE0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
const uint8_t ICON_CHIP[72] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xAA, 0x80, 0x02, 0xAA, 0x80,
  0x02, 0xAA, 0x80, 0x02, 0xAA, 0x80, 0x3F, 0xFF, 0xFC, 0x03, 0xFF, 0xC0,
  0x3F, 0x00, 0xFC, 0x03, 0x00, 0xC0, 0x3F, 0x3C, 0xFC, 0x03, 0x3C, 0xC0,
  0x3F, 0x3C, 0xFC, 0x03, 0x3C, 0xC0, 0x3F, 0x00, 0xFC, 0x03, 0x00, 0xC0,
  0x3F, 0xFF, 0xFC, 0x03, 0xFF, 0xC0, 0x02, 0xAA, 0x80, 0x02, 0xAA, 0x80,
  0x02, 0xAA, 0x80, 0x02, 0xAA, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
const uint8_t ICON_THERMO[72] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x3C, 0x00,
  0x00, 0xFF, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x3C, 0x00, 0x00, 0xFF, 0x00,
  0x00, 0x3C, 0x00, 0x00, 0x3C, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x3C, 0x00,
  0x00, 0x3C, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x18, 0x00, 0x00, 0x3C, 0x00,
  0x00, 0x7E, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x3C, 0x00,
  0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
const uint8_t ICON_GAMEPAD[72] PROGMEM = {
  0x00, 0x10, 0x00, 0x00, 0x38, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,
  0x03, 0xFF, 0xC0, 0x0C, 0x00, 0x30, 0x10, 0x00, 0x08, 0x20, 0x00, 0x04,
  0x40, 0xC3, 0x02, 0x41, 0x45, 0x02, 0x42, 0x42, 0x82, 0x40, 0xC3, 0x02,
  0x41, 0x45, 0x02, 0x40, 0x3C, 0x02, 0x40, 0x00, 0x02, 0x41, 0x86, 0x02,
  0x42, 0x49, 0x02, 0x41, 0x86, 0x02, 0x42, 0x49, 0x02, 0x20, 0x00, 0x04,
  0x10, 0x00, 0x08, 0x0C, 0x00, 0x30, 0x03, 0xFF, 0xC0, 0x00, 0x00, 0x00,
};
const uint8_t ICON_CALC[72] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xE0,
  0x04, 0x00, 0x20, 0x05, 0xFF, 0xA0, 0x05, 0xFF, 0xA0, 0x04, 0x00, 0x20,
  0x05, 0xFF, 0xA0, 0x04, 0x00, 0x20, 0x04, 0xDB, 0x20, 0x04, 0xDB, 0x20,
  0x04, 0x00, 0x20, 0x04, 0xDB, 0x20, 0x04, 0xDB, 0x20, 0x04, 0x00, 0x20,
  0x04, 0xDB, 0x20, 0x04, 0xDB, 0x20, 0x04, 0x00, 0x20, 0x05, 0xFF, 0xA0,
  0x07, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
const uint8_t ICON_CLOCK[72] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0xFF, 0x00, 0x01, 0xC1, 0x80,
  0x03, 0x40, 0xC0, 0x06, 0x20, 0x60, 0x06, 0x38, 0x60, 0x06, 0x3F, 0xE0,
  0x06, 0x38, 0x60, 0x06, 0x00, 0x60, 0x06, 0x00, 0x60, 0x03, 0x00, 0xC0,
  0x01, 0x81, 0x80, 0x00, 0xFF, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
const uint8_t ICON_BRUSH[72] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x0F, 0x00,
  0x00, 0x0F, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x18, 0x40,
  0x00, 0x38, 0x20, 0x00, 0x30, 0x20, 0x00, 0x70, 0x00, 0x00, 0xE0, 0x00,
  0x00, 0xC0, 0x00, 0x01, 0xC0, 0x00, 0x01, 0x80, 0x00, 0x03, 0x80, 0x00,
  0x07, 0x00, 0x00, 0x06, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x0C, 0x00, 0x00,
  0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
const uint8_t ICON_GEAR[72] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00,
  0x00, 0x18, 0x00, 0x06, 0x18, 0x60, 0x03, 0x7E, 0xC0, 0x01, 0xFF, 0x80,
  0x01, 0x81, 0x80, 0x03, 0x00, 0xC0, 0x03, 0x00, 0xC0, 0x1F, 0x00, 0xFC,
  0x03, 0x00, 0xC0, 0x03, 0x00, 0xC0, 0x03, 0x00, 0xC0, 0x01, 0x81, 0x80,
  0x03, 0xFF, 0xC0, 0x06, 0x7E, 0x60, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00,
  0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

struct Alien {
    int16_t x, y;
    bool vivo;
    uint8_t tipo;
};

struct EstadoJuego {
    uint8_t juegoSeleccionado;
    bool gameOver;
    bool victoria;
    unsigned long ultimoFrame;
    bool sonidoActivo;
    unsigned long inicioSonido;
    int frecuenciaSonido;

    int16_t paletaJugadorY;
    int16_t paletaCpuY;
    int16_t bolaX, bolaY;
    int8_t bolaVelX, bolaVelY;
    int8_t velCpu;
    uint8_t puntosJugador;
    uint8_t puntosCpu;
    bool activo;
    bool pausado;

    int16_t naveX;
    int16_t balaX, balaY;
    bool balaActiva;
    Alien aliens[SI_FILAS][SI_COLUMNAS];
    float alienVelX;
    unsigned long ultimoDisparoAuto;
    uint16_t aliensVivos;
    uint8_t frameAnimacion;

    uint8_t pongDificultad; // 0 = Normal, 1 = Alta
};

struct Toast {
    char mensaje[64];
    uint16_t color;
    unsigned long inicio;
    uint16_t duracion;
    bool activo;
};

struct ConfigSistema {
    bool sonidoActivo;
    uint8_t brilloPantalla;
    bool screensaverActivo;
    uint8_t temaColor;
    uint32_t tiempoEncendido;
};

struct EstadoCalc {
    char display[16];
    char operandoA[16];
    char operandoB[16];
    char operador;
    bool ingresandoB;
    bool resultadoMostrado;
    bool error;
};

struct EstadoCronometro {
    bool corriendo;
    unsigned long tiempoInicio;
    unsigned long tiempoPausado;
    unsigned long ultimoTiempo;
};

struct EstadoPaint {
    uint16_t colorSeleccionado;
    uint8_t grosorPincel;
    bool borrando;
    int ultimoX;
    int ultimoY;
    bool dibujando;
};

Adafruit_ILI9341 tft(PIN_TFT_CS, PIN_TFT_DC, PIN_TFT_RST);
XPT2046_Touchscreen ts(PIN_TOUCH_CS, PIN_TOUCH_IRQ);

bool sdLista = false;
EstadoJuego juego;
Toast toasts[MAX_TOASTS];
ConfigSistema config;
EstadoCalc calc;
EstadoCronometro cronometro;
EstadoCronometro temporizador;
EstadoPaint paint;
unsigned long ultimaActividad = 0;
bool screensaverActivo = false;
unsigned long tiempoInicioSO = 0;

char rutaActualSD[MAX_RUTA_SD] = "/";
float ultimaTemp = 0;
float ultimaHum = 0;
bool lecturaDHTOk = false;

const uint16_t PALETA_COLORES[] = {
    0xFFE0, 0x8010, 0xFB56, 0xF800, 0x001F,
    0x07E0, 0x0000, 0xA145, 0xFFFF, 0x8410,
    0xFD20
};
#define NUM_COLORES_PALETA 11

enum Pantalla {
    PANT_BOOT,
    PANT_MENU,
    PANT_ARCHIVOS,
    PANT_NOTAS,
    PANT_INFO,
    PANT_TEMP,
    PANT_MENU_JUEGOS,
    PANT_PONG_MENU,
    PANT_PONG,
    PANT_SPACE,
    PANT_CALCULADORA,
    PANT_RELOJ,
    PANT_PAINT,
    PANT_CONFIG,
    PANT_MEMORIA,
};
Pantalla pantallaActual = PANT_BOOT;

void dibujarBotonIcono(int x, int y, int ancho, int alto, const uint8_t* icono, uint16_t colorIcono, const char* subtitulo);
void renderizarBoot();
void renderizarMenu();
void renderizarMenuJuegos();
void renderizarPongMenu();
void manejarPongMenu(int x, int y);
void renderizarExploradorMejorado();
void renderizarNotas();
void renderizarInfo();
void renderizarTemperatura();
void actualizarDHT();
void renderizarCalculadora();
void renderizarReloj();
void renderizarPaint();
void renderizarConfiguracion();
void renderizarMemoria();
void iniciarPong();
void renderizarPong();
void renderizarCampoPong();
void dibujarPaletaPong(int x, int y, uint16_t color);
void borrarPaletaPong(int x, int y);
void dibujarBolaPong(int x, int y);
void borrarBolaPong(int x, int y);
void dibujarMarcadorPong();
void renderizarGameOverPong();
void procesarPong();
void moverBolaPong();
void actualizarCpuPong();
void actualizarJugadorTouchPong(int touchY);
void resetearBolaPong();
void sonidoRebotePong();
void sonidoPuntoPong();

void iniciarSpaceInvaders();
void loopSpaceInvaders();
void dibujarFondoJuego(const char* titulo);
void dibujarNaveEspacial(int x, int y, uint16_t color, uint16_t colorMotor);
void borrarNaveEspacial(int x, int y);
void dibujarAlienNave(int x, int y, uint8_t tipo, uint16_t color);
void borrarAlienNave(int x, int y);
void dibujarEstrellasFondo();
void dibujarExplosion(int x, int y);
void renderizarGameOverSpace();

void iniciarCalculadora();
void manejarTouchCalculadora(int x, int y);
void calcPresionarTecla(char tecla);
void calcActualizarDisplay();
float calcOperar(float a, float b, char op);
void calcDibujarBoton(int x, int y, int w, int h, const char* label, uint16_t colorFondo, uint16_t colorTexto);
void calcDibujarTeclado();
void calcFormatearResultado(float valor, char* destino, size_t len);

void iniciarReloj();
void manejarTouchReloj(int x, int y);
void cronometroActualizarDisplay();
void temporizadorActualizarDisplay();
void dibujarBotonControl(int x, int y, int w, int h, const char* label, uint16_t color);

void iniciarPaint();
void manejarTouchPaint(int x, int y);
void paintDibujarPaletaColores();
void paintDibujarControles();

void manejarTouchConfiguracion(int x, int y);
void dibujarInterruptor(int x, int y, bool activo, const char* etiqueta);
void dibujarDeslizador(int x, int y, int w, int valor, int maxVal, const char* etiqueta);

void actualizarMemoriaDisplay();
void manejarArchivosMejorado(int x, int y);
void exploradorEntrarDirectorio(const char* nombre);
void exploradorSubirDirectorio();
void exploradorEliminarArchivo(const char* nombre);
void exploradorCrearArchivo(const char* nombre);

void dibujarEncabezado(const char* titulo);
void dibujarBoton(int x, int y, int ancho, int alto, const char* etiqueta, const char* subtitulo);
void dibujarPanel(int x, int y, int ancho, int alto, const char* titulo);
void dibujarTarjeta(int x, int y, int ancho, int alto, uint16_t colorFondo);
void dibujarBarraProgreso(int x, int y, int ancho, int alto, int valor, int maxVal, uint16_t colorRelleno);
void dibujarToast(const char* mensaje, uint16_t color, uint16_t duracion);
void actualizarToasts();
void dibujarDialogoModal(const char* titulo, const char* mensaje, bool conConfirmar);
bool manejarDialogoModal(int x, int y);

void manejarMenuPrincipal(int x, int y);
void manejarMenuJuegos(int x, int y);
void manejarInfo(int x, int y);
bool obtenerTouch(int &x, int &y);
bool obtenerTouchDirecto(int &x, int &y);
bool enRectangulo(int tx, int ty, int rx, int ry, int rw, int rh);

void beepBoton();
void sonidoEfecto(int freq, int ms);

void reiniciarActividad();
void verificarScreensaver();
void activarScreensaver();
void desactivarScreensaver();
uint32_t obtenerMemoriaLibre();
uint32_t obtenerMemoriaTotal();
void formatearBytes(uint32_t bytes, char* salida, size_t len);
unsigned long obtenerTiempoEncendido();
void formatearTiempo(unsigned long ms, char* salida, size_t len);

void truncarTexto(const char* texto, char* salida, int maxChars);
bool esDirectorio(const char* ruta);
void concatenarRuta(const char* base, const char* nombre, char* salida, size_t len);
void dibujarFilaMemoria(const char* etiqueta, uint32_t valor, int y);

void dibujarBotonVolverUniversal();
bool touchEnBotonVolver(int x, int y);
bool manejarBotonVolverUniversal(int x, int y);
void paintDibujarBotonesSuperiores();

void dibujarBotonVolverUniversal() {
    dibujarTarjeta(BTN_VOLVER_U_X, BTN_VOLVER_U_Y, BTN_VOLVER_U_W, BTN_VOLVER_U_H, C_BOTON_INACTIVO);
    tft.drawRect(BTN_VOLVER_U_X, BTN_VOLVER_U_Y, BTN_VOLVER_U_W, BTN_VOLVER_U_H, C_BORDE);
    tft.setTextColor(C_ERROR);
    tft.setTextSize(2);
    tft.setCursor(BTN_VOLVER_U_X + 22, BTN_VOLVER_U_Y + 6);
    tft.print("X");
}

bool touchEnBotonVolver(int x, int y) {
    return enRectangulo(x, y, BTN_VOLVER_U_X, BTN_VOLVER_U_Y, BTN_VOLVER_U_W, BTN_VOLVER_U_H);
}

bool manejarBotonVolverUniversal(int x, int y) {
    if (touchEnBotonVolver(x, y)) {
        beepBoton();
        renderizarMenu();
        return true;
    }
    return false;
}

void paintDibujarBotonesSuperiores() {
    dibujarTarjeta(BTN_PAINT_LIMPIAR_X, BTN_PAINT_LIMPIAR_Y, BTN_PAINT_LIMPIAR_W, BTN_PAINT_LIMPIAR_H, C_BOTON_INACTIVO);
    tft.drawRect(BTN_PAINT_LIMPIAR_X, BTN_PAINT_LIMPIAR_Y, BTN_PAINT_LIMPIAR_W, BTN_PAINT_LIMPIAR_H, C_BORDE);
    tft.setTextColor(C_TEXTO_PRINCIPAL);
    tft.setTextSize(1);
    tft.setCursor(BTN_PAINT_LIMPIAR_X + 8, BTN_PAINT_LIMPIAR_Y + 10);
    tft.print("LIMPIAR");

    dibujarTarjeta(BTN_PAINT_GUARDAR_X, BTN_PAINT_GUARDAR_Y, BTN_PAINT_GUARDAR_W, BTN_PAINT_GUARDAR_H, C_BOTON_INACTIVO);
    tft.drawRect(BTN_PAINT_GUARDAR_X, BTN_PAINT_GUARDAR_Y, BTN_PAINT_GUARDAR_W, BTN_PAINT_GUARDAR_H, C_BORDE);
    tft.setCursor(BTN_PAINT_GUARDAR_X + 8, BTN_PAINT_GUARDAR_Y + 10);
    tft.print("GUARDAR");
}

void setup() {
    Serial.begin(115200);
    Serial.println(F("\n[LuvianOS v5.0] Secuencia de inicio iniciada..."));

    pinMode(PIN_BUZZER, OUTPUT);
    digitalWrite(PIN_BUZZER, LOW);

    pinMode(PIN_TFT_CS, OUTPUT);   digitalWrite(PIN_TFT_CS, HIGH);
    pinMode(PIN_TOUCH_CS, OUTPUT); digitalWrite(PIN_TOUCH_CS, HIGH);
    pinMode(PIN_SD_CS, OUTPUT);    digitalWrite(PIN_SD_CS, HIGH);

    // Inicializar display lo antes posible para mostrar boot
    tft.begin();
    tft.setRotation(3);

    renderizarBoot();

    // --- Barra de carga real ---
    // Paso 1: Touch controller (10%)
    ts.begin();
    ts.setRotation(3);
    actualizarBarraBoot(10);

    // Paso 2: Sensor DHT (25%)
    dht.begin();
    actualizarBarraBoot(25);

    // Paso 3: Semilla aleatoria (30%)
    randomSeed(analogRead(0));
    actualizarBarraBoot(30);

    // Paso 4: Configuracion por defecto (40%)
    config.sonidoActivo = true;
    config.brilloPantalla = 255;
    config.screensaverActivo = true;
    config.temaColor = 0;
    config.tiempoEncendido = 0;
    actualizarBarraBoot(40);

    // Paso 5: Inicializar estructuras de sistema (50%)
    for (int i = 0; i < MAX_TOASTS; i++) {
        toasts[i].activo = false;
    }
    cronometro.corriendo = false;
    cronometro.tiempoInicio = 0;
    cronometro.tiempoPausado = 0;
    temporizador.corriendo = false;
    temporizador.tiempoInicio = 0;
    temporizador.tiempoPausado = 60000;
    paint.colorSeleccionado = 0x0000;
    paint.grosorPincel = 2;
    paint.borrando = false;
    paint.dibujando = false;
    paint.ultimoX = -1;
    paint.ultimoY = -1;
    tiempoInicioSO = millis();
    ultimaActividad = millis();
    actualizarBarraBoot(50);

    // Paso 6: LED de actividad (60%)
    actualizarBarraBoot(60);

    // Paso 7: SD Card (puede tardar) -> 80% o 100%
    if (SD.begin(PIN_SD_CS)) {
        sdLista = true;
        Serial.println(F("[SD] Inicializada correctamente"));
        actualizarBarraBoot(75);
        cargarConfiguracionSD();
        actualizarBarraBoot(90);
    } else {
        sdLista = false;
        Serial.println(F("[SD] Tarjeta no detectada o error"));
        actualizarBarraBoot(100);
    }

    // Paso 8: Finalizar (100%)
    if (sdLista) {
        actualizarBarraBoot(100);
    }

    delay(400); // Pequena pausa para apreciar el 100%

    renderizarMenu();
    dibujarToast("Luvian OS v5.0 listo", C_TOAST_EXITO, 2000);
    Serial.println(F("[LuvianOS v5.0] Sistema listo"));
}

void loop() {
    verificarScreensaver();

    actualizarToasts();

    if (pantallaActual == PANT_PONG) {
        procesarPong();
        return;
    }
    if (pantallaActual == PANT_SPACE) {
        loopSpaceInvaders();
        return;
    }

    if (pantallaActual == PANT_TEMP) {
        static unsigned long ultDHT = 0;
        if (millis() - ultDHT > 2000) {
            ultDHT = millis();
            actualizarDHT();
        }
    }

    if (pantallaActual == PANT_RELOJ) {
        static unsigned long ultReloj = 0;
        if (millis() - ultReloj > 100) {
            ultReloj = millis();
            cronometroActualizarDisplay();
            temporizadorActualizarDisplay();
        }
    }

    if (pantallaActual == PANT_MEMORIA) {
        static unsigned long ultMem = 0;
        if (millis() - ultMem > 1000) {
            ultMem = millis();
            actualizarMemoriaDisplay();
        }
    }
    int x, y;
    if (obtenerTouch(x, y)) {
        reiniciarActividad();

        if (screensaverActivo) {
            desactivarScreensaver();
            return;
        }

        switch (pantallaActual) {
            case PANT_MENU:          manejarMenuPrincipal(x, y);      break;
            case PANT_ARCHIVOS:      manejarArchivosMejorado(x, y);   break;
            case PANT_NOTAS:         if (manejarBotonVolverUniversal(x, y)) return; break;
            case PANT_INFO:          manejarInfo(x, y);               break;
            case PANT_TEMP:          if (manejarBotonVolverUniversal(x, y)) return; break;
            case PANT_MENU_JUEGOS:   manejarMenuJuegos(x, y);         break;
            case PANT_PONG_MENU:     manejarPongMenu(x, y);           break;
            case PANT_CALCULADORA:   manejarTouchCalculadora(x, y);   break;
            case PANT_RELOJ:         manejarTouchReloj(x, y);         break;
            case PANT_PAINT:         manejarTouchPaint(x, y);         break;
            case PANT_CONFIG:        manejarTouchConfiguracion(x, y); break;
            case PANT_MEMORIA:       if (manejarBotonVolverUniversal(x, y)) return; break;
            default:                 if (manejarBotonVolverUniversal(x, y)) return; break;
        }
    }
}

void reiniciarActividad() {
    ultimaActividad = millis();
}

void verificarScreensaver() {
    if (!config.screensaverActivo || screensaverActivo) return;
    if (millis() - ultimaActividad > SCREENSAVER_TIMEOUT) {
        activarScreensaver();
    }
}

void activarScreensaver() {
    screensaverActivo = true;
    tft.fillScreen(C_FONDO_PRINCIPAL);
    tft.setTextColor(C_MARCA_PRIMARIO);
    tft.setTextSize(2);
    tft.setCursor(60, 100);
    tft.print("Luvian OS");
    tft.setTextSize(1);
    tft.setTextColor(C_TEXTO_TERCIARIO);
    tft.setCursor(80, 130);
    tft.print("Toca para despertar");

}

void desactivarScreensaver() {
    screensaverActivo = false;
    reiniciarActividad();
    switch (pantallaActual) {
        case PANT_MENU:          renderizarMenu(); break;
        case PANT_ARCHIVOS:      renderizarExploradorMejorado(); break;
        case PANT_TEMP:          renderizarTemperatura(); break;
        case PANT_RELOJ:         renderizarReloj(); break;
        case PANT_PAINT:         renderizarPaint(); break;
        default:                 renderizarMenu(); break;
    }
}

uint32_t obtenerMemoriaLibre() {
    return ESP.getFreeHeap();
}

uint32_t obtenerMemoriaTotal() {
    return ESP.getHeapSize();
}

void formatearBytes(uint32_t bytes, char* salida, size_t len) {
    if (bytes < 1024) {
        snprintf(salida, len, "%lu B", bytes);
    } else if (bytes < 1024 * 1024) {
        snprintf(salida, len, "%lu KB", bytes / 1024);
    } else {
        snprintf(salida, len, "%lu MB", bytes / (1024 * 1024));
    }
}

unsigned long obtenerTiempoEncendido() {
    return millis() - tiempoInicioSO;
}

void formatearTiempo(unsigned long ms, char* salida, size_t len) {
    unsigned long seg = ms / 1000;
    unsigned long min = seg / 60;
    unsigned long hor = min / 60;
    seg %= 60;
    min %= 60;
    snprintf(salida, len, "%02lu:%02lu:%02lu", hor, min, seg);
}

void truncarTexto(const char* texto, char* salida, int maxChars) {
    int len = strlen(texto);
    if (len <= maxChars) {
        strcpy(salida, texto);
    } else {
        strncpy(salida, texto, maxChars - 3);
        salida[maxChars - 3] = '\0';
        strcat(salida, "...");
    }
}

bool esDirectorio(const char* ruta) {
    File f = SD.open(ruta);
    if (!f) return false;
    bool isDir = f.isDirectory();
    f.close();
    return isDir;
}

void concatenarRuta(const char* base, const char* nombre, char* salida, size_t len) {
    if (strcmp(base, "/") == 0) {
        snprintf(salida, len, "/%s", nombre);
    } else {
        snprintf(salida, len, "%s/%s", base, nombre);
    }
}

void cargarConfiguracionSD() {
    File f = SD.open("/luvian.cfg");
    if (!f) return;
    String linea;
    while (f.available()) {
        linea = f.readStringUntil('\n');
        linea.trim();
        if (linea.startsWith("sonido=")) {
            config.sonidoActivo = linea.substring(7).toInt() == 1;
        } else if (linea.startsWith("brillo=")) {
            config.brilloPantalla = constrain(linea.substring(7).toInt(), 50, 255);
        } else if (linea.startsWith("screensaver=")) {
            config.screensaverActivo = linea.substring(12).toInt() == 1;
        } else if (linea.startsWith("tema=")) {
            config.temaColor = linea.substring(5).toInt();
        }
    }
    f.close();
}

void guardarConfiguracionSD() {
    if (!sdLista) return;
    SD.remove("/luvian.cfg");
    File f = SD.open("/luvian.cfg", FILE_WRITE);
    if (!f) return;
    f.print("sonido="); f.println(config.sonidoActivo ? 1 : 0);
    f.print("brillo="); f.println(config.brilloPantalla);
    f.print("screensaver="); f.println(config.screensaverActivo ? 1 : 0);
    f.print("tema="); f.println(config.temaColor);
    f.close();
}



void beepBoton() {
    if (!config.sonidoActivo) return;
    tone(PIN_BUZZER, 1000, 50);
    delay(55);
    noTone(PIN_BUZZER);
}

void sonidoEfecto(int freq, int ms) {
    if (!config.sonidoActivo) return;
    tone(PIN_BUZZER, freq, ms);
    juego.sonidoActivo = true;
    juego.inicioSonido = millis();
    juego.frecuenciaSonido = freq;
}

bool obtenerTouch(int &x, int &y) {
    if (!ts.touched()) return false;

    TS_Point p = ts.getPoint();

    if (p.z < 100) return false;

    x = map(p.x, TS_MAXX, TS_MINX, 0, ANCHO_PANTALLA);
    y = map(p.y, TS_MAXY, TS_MINY, 0, ALTO_PANTALLA);
    x = constrain(x, 0, ANCHO_PANTALLA - 1);
    y = constrain(y, 0, ALTO_PANTALLA - 1);

    delay(80);
    return true;
}

bool obtenerTouchDirecto(int &x, int &y) {
    if (!ts.touched()) return false;
    TS_Point p = ts.getPoint();
    if (p.z < 100) return false;
    x = map(p.x, TS_MAXX, TS_MINX, 0, ANCHO_PANTALLA);
    y = map(p.y, TS_MAXY, TS_MINY, 0, ALTO_PANTALLA);
    x = constrain(x, 0, ANCHO_PANTALLA - 1);
    y = constrain(y, 0, ALTO_PANTALLA - 1);
    return true;
}

bool enRectangulo(int tx, int ty, int rx, int ry, int rw, int rh) {
    return (tx >= rx && tx <= rx + rw && ty >= ry && ty <= ry + rh);
}

void dibujarToast(const char* mensaje, uint16_t color, uint16_t duracion) {
    int idx = -1;
    for (int i = 0; i < MAX_TOASTS; i++) {
        if (!toasts[i].activo) {
            idx = i;
            break;
        }
    }
    if (idx == -1) idx = 0;

    strncpy(toasts[idx].mensaje, mensaje, 63);
    toasts[idx].mensaje[63] = '\0';
    toasts[idx].color = color;
    toasts[idx].inicio = millis();
    toasts[idx].duracion = duracion;
    toasts[idx].activo = true;

    int yPos = 210 - (idx * 22);
    int ancho = strlen(mensaje) * 6 + 20;
    int xPos = (ANCHO_PANTALLA - ancho) / 2;

    dibujarTarjeta(xPos, yPos, ancho, 20, C_TOAST_FONDO);
    tft.drawRect(xPos, yPos, ancho, 20, color);
    tft.setTextColor(color);
    tft.setTextSize(1);
    tft.setCursor(xPos + 10, yPos + 6);
    tft.print(mensaje);
}

void actualizarToasts() {
    for (int i = 0; i < MAX_TOASTS; i++) {
        if (toasts[i].activo && (millis() - toasts[i].inicio > toasts[i].duracion)) {
            toasts[i].activo = false;
            int yPos = 210 - (i * 22);
            int ancho = strlen(toasts[i].mensaje) * 6 + 20;
            int xPos = (ANCHO_PANTALLA - ancho) / 2;
            dibujarTarjeta(xPos, yPos, ancho, 20, C_FONDO_PRINCIPAL);
        }
    }
}

void renderizarBoot() {
    pantallaActual = PANT_BOOT;
    tft.fillScreen(C_FONDO_PRINCIPAL);

    int marcoX = 25, marcoY = 55, marcoAncho = 270, marcoAlto = 130;
    tft.drawRect(marcoX, marcoY, marcoAncho, marcoAlto, C_BORDE);
    tft.drawRect(marcoX + 1, marcoY + 1, marcoAncho - 2, marcoAlto - 2, C_BORDE_ACTIVO);
    tft.drawRect(marcoX + 2, marcoY + 2, marcoAncho - 4, marcoAlto - 4, C_BORDE);

    const char* marca = "Luvian";
    int16_t marcaX = (ANCHO_PANTALLA - (int16_t)(strlen(marca) * 18)) / 2;
    int16_t marcaY = marcoY + 45;
    tft.setTextColor(C_MARCA_PRIMARIO);
    tft.setTextSize(3);
    tft.setCursor(marcaX, marcaY);
    tft.print(marca);

    tft.drawRect(BOOT_BAR_X, BOOT_BAR_Y, BOOT_BAR_W, BOOT_BAR_H, C_BORDE);
    tft.fillRect(BOOT_BAR_X + 1, BOOT_BAR_Y + 1, BOOT_BAR_W - 2, BOOT_BAR_H - 2, C_FONDO_SECUNDARIO);
}

void actualizarBarraBoot(uint8_t porcentaje) {
    int anchoRelleno = map(constrain(porcentaje, 0, 100), 0, 100, 0, BOOT_BAR_W - 2);
    if (anchoRelleno > 0) {
        tft.fillRect(BOOT_BAR_X + 1, BOOT_BAR_Y + 1, anchoRelleno, BOOT_BAR_H - 2, C_MARCA_PRIMARIO);
    }
}

void renderizarMenu() {
    pantallaActual = PANT_MENU;
    tft.fillScreen(C_FONDO_PRINCIPAL);

    dibujarEncabezado("Menu Principal");

    dibujarBotonIcono(BTN_COL1_X, BTN_FILA1_Y, BTN_ANCHO, BTN_FILA1_ALTO, ICON_FOLDER, C_ICON_FOLDER, "Explorador SD");
    dibujarBotonIcono(BTN_COL2_X, BTN_FILA1_Y, BTN_ANCHO, BTN_FILA1_ALTO, ICON_CHIP, C_ICON_CHIP, "Info y Memoria");
    dibujarBotonIcono(BTN_COL3_X, BTN_FILA1_Y, BTN_ANCHO, BTN_FILA1_ALTO, ICON_THERMO, C_ICON_THERMO, "Temp/Hum");

    dibujarBotonIcono(BTN_COL1_X, BTN_FILA2_Y, BTN_ANCHO, BTN_FILA1_ALTO, ICON_GAMEPAD, C_ICON_GAMEPAD, "Arcade");
    dibujarBotonIcono(BTN_COL2_X, BTN_FILA2_Y, BTN_ANCHO, BTN_FILA1_ALTO, ICON_CALC, C_ICON_CALC, "Calculadora");
    dibujarBotonIcono(BTN_COL3_X, BTN_FILA2_Y, BTN_ANCHO, BTN_FILA1_ALTO, ICON_CLOCK, C_ICON_CLOCK, "Cronometro");

    dibujarBotonIcono(BTN_COL1_X, BTN_FILA3_Y, BTN_ANCHO, BTN_FILA1_ALTO, ICON_BRUSH, C_ICON_BRUSH, "Dibujo");
    dibujarBotonIcono(BTN_COL2_X, BTN_FILA3_Y, BTN_ANCHO, BTN_FILA1_ALTO, ICON_GEAR, C_ICON_GEAR, "Ajustes");
    tft.fillRect(0, 225, ANCHO_PANTALLA, 15, C_FONDO_SECUNDARIO);
    tft.drawFastHLine(0, 225, ANCHO_PANTALLA, C_BORDE);

    tft.setTextSize(1);
    tft.setTextColor(sdLista ? C_EXITO : C_ERROR);
    tft.setCursor(6, 229);
    tft.print(sdLista ? "SD OK" : "SD --");

    tft.setTextColor(C_TEXTO_TERCIARIO);
    tft.setCursor(60, 229);
    char tiempoStr[16];
    formatearTiempo(obtenerTiempoEncendido(), tiempoStr, sizeof(tiempoStr));
    tft.print(tiempoStr);

    tft.setCursor(130, 229);
    tft.print("LuvianOS v5.0");

    char memStr[16];
    formatearBytes(obtenerMemoriaLibre(), memStr, sizeof(memStr));
    tft.setTextColor(C_TEXTO_SECUNDARIO);
    tft.setCursor(240, 229);
    tft.print(memStr);
}

void renderizarMenuJuegos() {
    pantallaActual = PANT_MENU_JUEGOS;
    tft.fillScreen(C_FONDO_PRINCIPAL);

    dibujarEncabezado("Centro de Juegos");

    dibujarBoton(BTN_PONG_X,  BTN_JUEGO_Y, BTN_JUEGO_ANCHO, BTN_JUEGO_ALTO, "PONG",  "Clasico");
    dibujarBoton(BTN_SPACE_X, BTN_JUEGO_Y, BTN_JUEGO_ANCHO, BTN_JUEGO_ALTO, "SPACE", "Invasores");

    dibujarPanel(10, 168, 300, 26, nullptr);
    tft.setTextColor(C_TEXTO_TERCIARIO);
    tft.setTextSize(1);
    tft.setCursor(18, 175);
    tft.print("Mejora tus habilidades!");
}

// === NUEVO: Menu de dificultad para Pong ===
void renderizarPongMenu() {
    pantallaActual = PANT_PONG_MENU;
    tft.fillScreen(C_FONDO_PRINCIPAL);
    dibujarEncabezado("Pong - Dificultad");

    dibujarBoton(40, 70, 240, 50, "NORMAL", "Bola lenta, CPU facil");
    dibujarBoton(40, 140, 240, 50, "ALTA", "Bola rapida, CPU actual");

    dibujarPanel(10, 205, 300, 26, nullptr);
    tft.setTextColor(C_TEXTO_TERCIARIO);
    tft.setTextSize(1);
    tft.setCursor(18, 212);
    tft.print("Selecciona modo antes de jugar");

    dibujarBotonVolverUniversal();
}

void manejarPongMenu(int x, int y) {
    if (manejarBotonVolverUniversal(x, y)) return;
    if (enRectangulo(x, y, 40, 70, 240, 50)) {
        beepBoton();
        juego.pongDificultad = 0;
        iniciarPong();
    } else if (enRectangulo(x, y, 40, 140, 240, 50)) {
        beepBoton();
        juego.pongDificultad = 1;
        iniciarPong();
    }
}

void renderizarExploradorMejorado() {
    pantallaActual = PANT_ARCHIVOS;
    tft.fillScreen(C_FONDO_PRINCIPAL);

    tft.fillRect(0, ENCABEZADO_Y, ANCHO_PANTALLA, ENCABEZADO_ALTO, C_FONDO_SECUNDARIO);
    tft.drawFastHLine(0, 0, ANCHO_PANTALLA, C_MARCA_PRIMARIO);
    dibujarBotonVolverUniversal();

    tft.setTextColor(C_MARCA_PRIMARIO);
    tft.setTextSize(1);
    tft.setCursor(BTN_VOLVER_U_X + BTN_VOLVER_U_W + 8, 12);
    tft.print("SD: ");
    tft.setTextColor(C_TEXTO_PRINCIPAL);
    char rutaTruncada[36];
    truncarTexto(rutaActualSD, rutaTruncada, 30);
    tft.print(rutaTruncada);
    tft.drawFastHLine(0, ENCABEZADO_ALTO - 1, ANCHO_PANTALLA, C_BORDE);

    if (!sdLista) {
        tft.setTextColor(C_ERROR);
        tft.setTextSize(2);
        tft.setCursor(40, 80);
        tft.print("SD No Detectada");
        tft.setTextColor(C_TEXTO_TERCIARIO);
        tft.setTextSize(1);
        tft.setCursor(50, 110);
        tft.print("Inserta una tarjeta SD valida");
        return;
    }

    File raiz = SD.open(rutaActualSD);
    if (!raiz) {
        tft.setTextColor(C_ERROR);
        tft.setCursor(15, 55);
        tft.print("Error al abrir directorio");
        return;
    }

    tft.setTextSize(1);
    int posY = 38;
    int cantidad = 0;
    int maxItems = 8;

    while (cantidad < maxItems) {
        File archivo = raiz.openNextFile();
        if (!archivo) break;

        const char* nombre = archivo.name();
        bool esDir = archivo.isDirectory();

        tft.setCursor(12, posY);
        if (esDir) {
            tft.setTextColor(C_ADVERTENCIA);
            tft.print("[DIR]");
        } else {
            tft.setTextColor(C_INFO);
            tft.print("[FIL]");
        }

        tft.setTextColor(C_TEXTO_PRINCIPAL);
        tft.setCursor(50, posY);
        char nombreTrunc[20];
        truncarTexto(nombre, nombreTrunc, 19);
        tft.print(nombreTrunc);

        if (!esDir) {
            tft.setTextColor(C_TEXTO_TERCIARIO);
            tft.setCursor(200, posY);
            char tamStr[12];
            formatearBytes(archivo.size(), tamStr, sizeof(tamStr));
            tft.print(tamStr);
        }

        archivo.close();
        posY += 16;
        cantidad++;
    }
    raiz.close();

    if (cantidad == 0) {
        tft.setTextColor(C_TEXTO_TERCIARIO);
        tft.setCursor(100, 80);
        tft.print("Directorio vacio");
    }

    dibujarBoton(10, 168, 95, 26, "NUEVO", nullptr);
    dibujarBoton(112, 168, 95, 26, "BORRAR", nullptr);
    dibujarBoton(214, 168, 95, 26, "SUBIR", nullptr);
}


void manejarArchivosMejorado(int x, int y) {
    if (manejarBotonVolverUniversal(x, y)) return;

    if (enRectangulo(x, y, 214, 168, 95, 26)) {
        beepBoton();
        exploradorSubirDirectorio();
        return;
    }
    if (enRectangulo(x, y, 10, 168, 95, 26)) {
        beepBoton();
        exploradorCrearArchivo("nuevo.txt");
        return;
    }
    if (enRectangulo(x, y, 112, 168, 95, 26)) {
        beepBoton();
        dibujarToast("Selecciona un archivo", C_TOAST_INFO, 2000);
        return;
    }

    if (y >= 38 && y < 168 && sdLista) {
        int idx = (y - 38) / 16;
        File raiz = SD.open(rutaActualSD);
        if (raiz) {
            int i = 0;
            while (i <= idx) {
                File f = raiz.openNextFile();
                if (!f) break;
                if (i == idx) {
                    if (f.isDirectory()) {
                        exploradorEntrarDirectorio(f.name());
                    } else {
                        char rutaCompleta[MAX_RUTA_SD];
                        concatenarRuta(rutaActualSD, f.name(), rutaCompleta, sizeof(rutaCompleta));
                        File archivo = SD.open(rutaCompleta);
                        if (archivo) {
                            pantallaActual = PANT_NOTAS;
                            tft.fillScreen(C_FONDO_PRINCIPAL);
                            dibujarEncabezado(f.name());

                            tft.setTextColor(C_TEXTO_PRINCIPAL);
                            tft.setTextSize(1);
                            int posY = 42;
                            String linea = "";
                            while (archivo.available() && posY < BTN_VOLVER_Y - 10) {
                                char c = archivo.read();
                                if (c == '\n' || c == '\r') {
                                    if (linea.length() > 0) {
                                        tft.setCursor(10, posY);
                                        tft.print(linea.substring(0, 40));
                                        posY += 13;
                                        linea = "";
                                    }
                                } else {
                                    linea += c;
                                }
                            }
                            if (linea.length() > 0 && posY < BTN_VOLVER_Y - 10) {
                                tft.setCursor(10, posY);
                                tft.print(linea.substring(0, 40));
                            }
                            archivo.close();
                            beepBoton();
                        }
                    }
                    f.close();
                    break;
                }
                f.close();
                i++;
            }
            raiz.close();
        }
    }
}

void exploradorEntrarDirectorio(const char* nombre) {
    if (strlen(rutaActualSD) == 1 && rutaActualSD[0] == '/') {
        snprintf(rutaActualSD, MAX_RUTA_SD, "/%s", nombre);
    } else {
        char nuevaRuta[MAX_RUTA_SD];
        snprintf(nuevaRuta, sizeof(nuevaRuta), "%s/%s", rutaActualSD, nombre);
        strncpy(rutaActualSD, nuevaRuta, MAX_RUTA_SD - 1);
        rutaActualSD[MAX_RUTA_SD - 1] = '\0';
    }
    renderizarExploradorMejorado();
}

void exploradorSubirDirectorio() {
    if (strcmp(rutaActualSD, "/") == 0) {
        dibujarToast("Ya estas en raiz", C_ADVERTENCIA, 1500);
        return;
    }
    char* ultimaBarra = strrchr(rutaActualSD, '/');
    if (ultimaBarra && ultimaBarra != rutaActualSD) {
        *ultimaBarra = '\0';
    } else {
        strcpy(rutaActualSD, "/");
    }
    renderizarExploradorMejorado();
}

void exploradorEliminarArchivo(const char* nombre) {
    if (!sdLista) return;
    char rutaCompleta[MAX_RUTA_SD];
    concatenarRuta(rutaActualSD, nombre, rutaCompleta, sizeof(rutaCompleta));
    if (SD.remove(rutaCompleta)) {
        dibujarToast("Archivo eliminado", C_TOAST_EXITO, 1500);
    } else {
        if (SD.rmdir(rutaCompleta)) {
            dibujarToast("Directorio eliminado", C_TOAST_EXITO, 1500);
        } else {
            dibujarToast("Error al eliminar", C_TOAST_ERROR, 2000);
        }
    }
    renderizarExploradorMejorado();
}

void exploradorCrearArchivo(const char* nombre) {
    if (!sdLista) return;
    char rutaCompleta[MAX_RUTA_SD];
    concatenarRuta(rutaActualSD, nombre, rutaCompleta, sizeof(rutaCompleta));
    File f = SD.open(rutaCompleta, FILE_WRITE);
    if (f) {
        f.println("// Archivo creado por Luvian OS v5.0");
        f.close();
        dibujarToast("Archivo creado", C_TOAST_EXITO, 1500);
    } else {
        dibujarToast("Error al crear archivo", C_TOAST_ERROR, 2000);
    }
    renderizarExploradorMejorado();
}

void renderizarNotas() {
    pantallaActual = PANT_NOTAS;
    tft.fillScreen(C_FONDO_PRINCIPAL);
    dibujarEncabezado("Visor de Texto");

    if (!sdLista) {
        tft.setTextColor(C_ERROR);
        tft.setTextSize(2);
        tft.setCursor(40, 80);
        tft.print("SD No Disponible");
        return;
    }

    File nota = SD.open("/notes.txt");
    if (!nota) {
        tft.setTextColor(C_TEXTO_SECUNDARIO);
        tft.setTextSize(1);
        tft.setCursor(15, 55);
        tft.print("Crea notes.txt en la SD");
        return;
    }

    tft.setTextColor(C_TEXTO_PRINCIPAL);
    tft.setTextSize(1);
    int posY = 42;
    String linea = "";

    while (nota.available() && posY < BTN_VOLVER_Y - 10) {
        char c = nota.read();
        if (c == '\n' || c == '\r') {
            if (linea.length() > 0) {
                tft.setCursor(10, posY);
                tft.print(linea.substring(0, 40));
                posY += 13;
                linea = "";
            }
        } else {
            linea += c;
        }
    }
    if (linea.length() > 0 && posY < BTN_VOLVER_Y - 10) {
        tft.setCursor(10, posY);
        tft.print(linea.substring(0, 40));
    }
    nota.close();
}

void renderizarTemperatura() {
    pantallaActual = PANT_TEMP;
    tft.fillScreen(C_FONDO_PRINCIPAL);

    dibujarEncabezado("Monitor Ambiental");
    actualizarDHT();
}

void actualizarDHT() {
    float temperatura = dht.readTemperature();
    float humedad = dht.readHumidity();
    lecturaDHTOk = !isnan(temperatura) && !isnan(humedad);

    if (lecturaDHTOk) {
        ultimaTemp = temperatura;
        ultimaHum = humedad;
    }

    tft.fillRect(8, 38, 304, 175, C_FONDO_PRINCIPAL);

    if (!lecturaDHTOk) {
        dibujarPanel(10, 50, 300, 60, nullptr);
        tft.setTextColor(C_ERROR);
        tft.setTextSize(1);
        tft.setCursor(20, 68);
        tft.print("Error de lectura del sensor DHT11");
        tft.setCursor(20, 84);
        tft.print("Verificar conexion en GPIO 16");

        if (ultimaTemp != 0) {
            tft.setTextColor(C_TEXTO_TERCIARIO);
            tft.setCursor(20, 120);
            tft.print("Ultima lectura: ");
            tft.print(ultimaTemp, 1);
            tft.print("C / ");
            tft.print(ultimaHum, 1);
            tft.print("%");
        }
        return;
    }

    dibujarTarjeta(10, 42, 145, 75, C_FONDO_SECUNDARIO);
    tft.drawRect(10, 42, 145, 75, C_BORDE);

    tft.setTextColor(C_TEXTO_SECUNDARIO);
    tft.setTextSize(1);
    tft.setCursor(18, 48);
    tft.print("TEMPERATURA");

    tft.setTextColor(C_MARCA_PRIMARIO);
    tft.setTextSize(3);
    char bufTemp[10];
    dtostrf(temperatura, 4, 1, bufTemp);
    tft.setCursor(18, 65);
    tft.print(bufTemp);

    tft.setTextSize(2);
    tft.setTextColor(C_TEXTO_TERCIARIO);
    tft.setCursor(100, 65);
    tft.print("\xF7" "C");

    dibujarTarjeta(165, 42, 145, 75, C_FONDO_SECUNDARIO);
    tft.drawRect(165, 42, 145, 75, C_BORDE);

    tft.setTextColor(C_TEXTO_SECUNDARIO);
    tft.setTextSize(1);
    tft.setCursor(173, 48);
    tft.print("HUMEDAD");

    tft.setTextColor(C_INFO);
    tft.setTextSize(3);
    char bufHum[10];
    dtostrf(humedad, 4, 1, bufHum);
    tft.setCursor(173, 65);
    tft.print(bufHum);

    tft.setTextSize(2);
    tft.setTextColor(C_TEXTO_TERCIARIO);
    tft.setCursor(255, 65);
    tft.print("%");

    int mapT = map((int)temperatura, 0, 50, 0, 140);
    mapT = constrain(mapT, 0, 140);
    dibujarBarraProgreso(15, 128, 140, 10, mapT, 140, C_MARCA_PRIMARIO);
    tft.setTextColor(C_TEXTO_TERCIARIO);
    tft.setTextSize(1);
    tft.setCursor(15, 141);
    tft.print("0");
    tft.setCursor(138, 141);
    tft.print("50C");

    int mapH = map((int)humedad, 0, 100, 0, 140);
    dibujarBarraProgreso(165, 128, 140, 10, mapH, 140, C_INFO);
    tft.setCursor(165, 141);
    tft.print("0%");
    tft.setCursor(288, 141);
    tft.print("100%");

    dibujarTarjeta(10, 155, 300, 45, C_FONDO_SECUNDARIO);
    tft.drawRect(10, 155, 300, 45, C_BORDE);

    tft.setTextColor(C_TEXTO_SECUNDARIO);
    tft.setTextSize(1);
    tft.setCursor(18, 162);
    tft.print("ESTADO:");

    tft.setTextColor(C_EXITO);
    tft.setCursor(70, 162);
    if (temperatura > 35) {
        tft.setTextColor(C_ADVERTENCIA);
        tft.print("CALOR");
    } else if (temperatura < 10) {
        tft.setTextColor(C_INFO);
        tft.print("FRIO");
    } else {
        tft.print("NORMAL");
    }

    tft.setTextColor(C_TEXTO_TERCIARIO);
    tft.setCursor(18, 178);
    tft.print("DHT11 | GPIO 16 | Auto: 2s");
}

void renderizarCalculadora() {
    pantallaActual = PANT_CALCULADORA;
    iniciarCalculadora();
}

void iniciarCalculadora() {
    strcpy(calc.display, "0");
    calc.operandoA[0] = '\0';
    calc.operandoB[0] = '\0';
    calc.operador = '\0';
    calc.ingresandoB = false;
    calc.resultadoMostrado = false;
    calc.error = false;

    tft.fillScreen(C_FONDO_PRINCIPAL);
    dibujarEncabezado("Calculadora");

    calcActualizarDisplay();
    calcDibujarTeclado();
}

void calcDibujarTeclado() {
    const char* teclas[] = {
        "7", "8", "9", "/",
        "4", "5", "6", "x",
        "1", "2", "3", "-",
        "C", "0", "=", "+"
    };
    const uint16_t coloresFondo[] = {
        C_BOTON_INACTIVO, C_BOTON_INACTIVO, C_BOTON_INACTIVO, C_BOTON_PRESIONADO,
        C_BOTON_INACTIVO, C_BOTON_INACTIVO, C_BOTON_INACTIVO, C_BOTON_PRESIONADO,
        C_BOTON_INACTIVO, C_BOTON_INACTIVO, C_BOTON_INACTIVO, C_BOTON_PRESIONADO,
        C_ERROR, C_BOTON_INACTIVO, C_EXITO, C_BOTON_PRESIONADO
    };

    for (int fila = 0; fila < 4; fila++) {
        for (int col = 0; col < 4; col++) {
            int x = CALC_COL1_X + col * 78;
            int y = CALC_BTN_FILA1_Y + fila * 40;
            int idx = fila * 4 + col;
            calcDibujarBoton(x, y, CALC_BTN_ANCHO, CALC_BTN_ALTO, teclas[idx],
                           coloresFondo[idx], C_TEXTO_PRINCIPAL);
        }
    }
}

void calcDibujarBoton(int x, int y, int w, int h, const char* label, uint16_t colorFondo, uint16_t colorTexto) {
    dibujarTarjeta(x, y, w, h, colorFondo);
    tft.drawRect(x, y, w, h, C_BORDE);

    tft.setTextColor(colorTexto);
    tft.setTextSize(2);
    int16_t tx = x + (w / 2) - (strlen(label) * 6);
    int16_t ty = y + (h / 2) - 8;
    tft.setCursor(tx, ty);
    tft.print(label);
}

void calcActualizarDisplay() {
    dibujarTarjeta(CALC_DISPLAY_X, CALC_DISPLAY_Y, CALC_DISPLAY_W, CALC_DISPLAY_ALTO, C_FONDO_SECUNDARIO);
    tft.drawRect(CALC_DISPLAY_X, CALC_DISPLAY_Y, CALC_DISPLAY_W, CALC_DISPLAY_ALTO, C_BORDE_ACTIVO);

    tft.setTextSize(2);
    if (calc.error) {
        tft.setTextColor(C_ERROR);
        tft.setCursor(20, CALC_DISPLAY_Y + 18);
        tft.print("Error");
        return;
    }

    const char* texto = calc.display;
    int len = strlen(texto);
    tft.setTextColor(C_TEXTO_PRINCIPAL);
    int px = CALC_DISPLAY_X + CALC_DISPLAY_W - (len * 12) - CALC_DISPLAY_PAD_R;
    if (px < CALC_DISPLAY_X + 10) px = CALC_DISPLAY_X + 10;
    tft.setCursor(px, CALC_DISPLAY_Y + 18);
    tft.print(texto);
}

void manejarTouchCalculadora(int x, int y) {
    if (manejarBotonVolverUniversal(x, y)) return;

    for (int fila = 0; fila < 4; fila++) {
        for (int col = 0; col < 4; col++) {
            int bx = CALC_COL1_X + col * 78;
            int by = CALC_BTN_FILA1_Y + fila * 40;
            if (enRectangulo(x, y, bx, by, CALC_BTN_ANCHO, CALC_BTN_ALTO)) {
                beepBoton();
                const char teclas[] = {'7','8','9','/','4','5','6','x','1','2','3','-','C','0','=','+'};
                char tecla = teclas[fila * 4 + col];
                calcPresionarTecla(tecla);

                uint16_t coloresOrig[] = {
                    C_BOTON_INACTIVO, C_BOTON_INACTIVO, C_BOTON_INACTIVO, C_BOTON_PRESIONADO,
                    C_BOTON_INACTIVO, C_BOTON_INACTIVO, C_BOTON_INACTIVO, C_BOTON_PRESIONADO,
                    C_BOTON_INACTIVO, C_BOTON_INACTIVO, C_BOTON_INACTIVO, C_BOTON_PRESIONADO,
                    C_ERROR, C_BOTON_INACTIVO, C_EXITO, C_BOTON_PRESIONADO
                };
                char labelStr[2] = {tecla, '\0'};
                calcDibujarBoton(bx, by, CALC_BTN_ANCHO, CALC_BTN_ALTO,
                    labelStr, C_MARCA_PRIMARIO, C_TEXTO_INVERTIDO);
                delay(80);
                int idx = fila * 4 + col;
                const char* labels[] = {"7","8","9","/","4","5","6","x","1","2","3","-","C","0","=","+"};
                calcDibujarBoton(bx, by, CALC_BTN_ANCHO, CALC_BTN_ALTO,
                    labels[idx], coloresOrig[idx], C_TEXTO_PRINCIPAL);
                return;
            }
        }
    }
}

void calcFormatearResultado(float valor, char* destino, size_t len) {
    char buf[16];
    dtostrf(valor, 15, 4, buf);
    char* p = buf + strlen(buf) - 1;
    while (p > buf && *p == ' ') p--;
    while (p > buf && *p == '0') p--;
    if (*p == '.') p--;
    *(p + 1) = '\0';
    char* inicio = buf;
    while (*inicio == ' ') inicio++;
    strncpy(destino, inicio, len - 1);
    destino[len - 1] = '\0';
}

void calcPresionarTecla(char tecla) {
    if (calc.error && tecla != 'C') {
        return;
    }

    if (tecla == 'C') {
        strcpy(calc.display, "0");
        calc.operandoA[0] = '\0';
        calc.operandoB[0] = '\0';
        calc.operador = '\0';
        calc.ingresandoB = false;
        calc.resultadoMostrado = false;
        calc.error = false;
        calcActualizarDisplay();
        return;
    }

    if (tecla == '=') {
        if (calc.operador != '\0' && calc.operandoA[0] != '\0') {
            float a = atof(calc.operandoA);
            float b = atof(calc.display);
            float resultado = calcOperar(a, b, calc.operador);
            if (calc.error) {
                strcpy(calc.display, "Error");
            } else {
                calcFormatearResultado(resultado, calc.display, sizeof(calc.display));
                strcpy(calc.operandoA, calc.display);
                calc.resultadoMostrado = true;
            }
            calc.operador = '\0';
            calc.ingresandoB = false;
            calc.operandoB[0] = '\0';
        }
        calcActualizarDisplay();
        return;
    }

    if (tecla == '+' || tecla == '-' || tecla == 'x' || tecla == '/') {
        if (calc.operador != '\0' && !calc.resultadoMostrado) {
            float a = atof(calc.operandoA);
            float b = atof(calc.display);
            float resultado = calcOperar(a, b, calc.operador);
            calcFormatearResultado(resultado, calc.operandoA, sizeof(calc.operandoA));
            strcpy(calc.display, calc.operandoA);
        } else {
            strcpy(calc.operandoA, calc.display);
        }
        calc.operador = tecla;
        calc.ingresandoB = true;
        calc.resultadoMostrado = false;
        calc.operandoB[0] = '\0';
        calcActualizarDisplay();
        return;
    }

    if (calc.resultadoMostrado || (calc.ingresandoB && calc.operandoB[0] == '\0')) {
        strcpy(calc.display, "");
        calc.resultadoMostrado = false;
    }
    if (strlen(calc.display) < 14) {
        if (strcmp(calc.display, "0") == 0) {
            calc.display[0] = tecla;
            calc.display[1] = '\0';
        } else {
            int len = strlen(calc.display);
            calc.display[len] = tecla;
            calc.display[len + 1] = '\0';
        }
    }
    if (calc.ingresandoB) {
        strcpy(calc.operandoB, calc.display);
    }
    calcActualizarDisplay();
}

float calcOperar(float a, float b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case 'x': return a * b;
        case '/':
            if (b == 0) {
                calc.error = true;
                return 0;
            }
            return a / b;
        default: return 0;
    }
}

void renderizarReloj() {
    pantallaActual = PANT_RELOJ;
    iniciarReloj();
}

void iniciarReloj() {
    tft.fillScreen(C_FONDO_PRINCIPAL);
    dibujarEncabezado("Reloj y Cronometro");

    dibujarPanel(10, 40, 300, 80, "CRONOMETRO");

    tft.setTextColor(C_MARCA_PRIMARIO);
    tft.setTextSize(3);
    tft.setCursor(25, 65);
    tft.print("00:00:00");

    dibujarBotonControl(15, 130, 90, 30, "INICIAR", C_EXITO);
    dibujarBotonControl(115, 130, 90, 30, "PAUSAR", C_ADVERTENCIA);
    dibujarBotonControl(215, 130, 90, 30, "RESET", C_ERROR);

    dibujarPanel(10, 170, 300, 55, "TEMPORIZADOR (1 min)");
    tft.setTextColor(C_TEXTO_PRINCIPAL);
    tft.setTextSize(2);
    tft.setCursor(30, 195);
    tft.print("01:00:00");
}

void dibujarBotonControl(int x, int y, int w, int h, const char* label, uint16_t color) {
    dibujarTarjeta(x, y, w, h, C_BOTON_INACTIVO);
    tft.drawRect(x, y, w, h, color);
    tft.setTextColor(color);
    tft.setTextSize(1);
    int16_t tx = x + (w / 2) - (strlen(label) * 3);
    tft.setCursor(tx, y + 10);
    tft.print(label);
}

void manejarTouchReloj(int x, int y) {
    if (manejarBotonVolverUniversal(x, y)) return;

    if (enRectangulo(x, y, 15, 130, 90, 30)) {
        beepBoton();
        if (!cronometro.corriendo) {
            if (cronometro.tiempoPausado > 0) {
                cronometro.tiempoInicio = millis() - cronometro.tiempoPausado;
            } else {
                cronometro.tiempoInicio = millis();
            }
            cronometro.corriendo = true;
            dibujarToast("Cronometro iniciado", C_TOAST_EXITO, 1000);
        }
    }
    else if (enRectangulo(x, y, 115, 130, 90, 30)) {
        beepBoton();
        if (cronometro.corriendo) {
            cronometro.tiempoPausado = millis() - cronometro.tiempoInicio;
            cronometro.corriendo = false;
            dibujarToast("Cronometro pausado", C_ADVERTENCIA, 1000);
        }
    }
    else if (enRectangulo(x, y, 215, 130, 90, 30)) {
        beepBoton();
        cronometro.corriendo = false;
        cronometro.tiempoInicio = 0;
        cronometro.tiempoPausado = 0;
        cronometro.ultimoTiempo = 0;
        dibujarPanel(10, 40, 300, 80, "CRONOMETRO");
        tft.setTextColor(C_MARCA_PRIMARIO);
        tft.setTextSize(3);
        tft.setCursor(25, 65);
        tft.print("00:00:00");
        dibujarToast("Cronometro reseteado", C_TOAST_INFO, 1000);
    }
    else if (enRectangulo(x, y, 10, 170, 300, 55)) {
        beepBoton();
        if (!temporizador.corriendo) {
            temporizador.tiempoInicio = millis();
            temporizador.corriendo = true;
            dibujarToast("Temporizador 1 min", C_TOAST_EXITO, 1000);
        }
    }
}

void cronometroActualizarDisplay() {
    unsigned long tiempoActual;
    if (cronometro.corriendo) {
        tiempoActual = millis() - cronometro.tiempoInicio;
    } else {
        tiempoActual = cronometro.tiempoPausado;
    }

    if (tiempoActual == cronometro.ultimoTiempo) return;
    cronometro.ultimoTiempo = tiempoActual;

    unsigned long totalSeg = tiempoActual / 1000;
    unsigned long hor = totalSeg / 3600;
    unsigned long min = (totalSeg % 3600) / 60;
    unsigned long seg = totalSeg % 60;

    char buf[12];
    snprintf(buf, sizeof(buf), "%02lu:%02lu:%02lu", hor, min, seg);

    dibujarTarjeta(12, 55, 296, 40, C_FONDO_SECUNDARIO);
    tft.setTextColor(C_MARCA_PRIMARIO);
    tft.setTextSize(3);
    tft.setCursor(30, 62);
    tft.print(buf);
}

void temporizadorActualizarDisplay() {
    if (!temporizador.corriendo) return;

    unsigned long transcurrido = millis() - temporizador.tiempoInicio;
    long restante = (long)temporizador.tiempoPausado - (long)transcurrido;

    if (restante <= 0) {
        temporizador.corriendo = false;
        restante = 0;
        dibujarToast("¡Tiempo terminado!", C_TOAST_EXITO, 3000);
        sonidoEfecto(1000, 500);
        delay(300);
        sonidoEfecto(1200, 500);
    }

    unsigned long totalSeg = restante / 1000;
    unsigned long min = totalSeg / 60;
    unsigned long seg = totalSeg % 60;

    char buf[12];
    snprintf(buf, sizeof(buf), "%02lu:%02lu:%02lu", min, seg, (restante % 1000) / 10);

    dibujarTarjeta(12, 190, 296, 20, C_FONDO_SECUNDARIO);
    tft.setTextColor(temporizador.corriendo ? C_INFO : C_EXITO);
    tft.setTextSize(2);
    tft.setCursor(35, 192);
    tft.print(buf);
}

void renderizarPaint() {
    pantallaActual = PANT_PAINT;
    iniciarPaint();
}

void iniciarPaint() {
    paint.colorSeleccionado = 0x0000;
    paint.grosorPincel = 2;
    paint.borrando = false;
    paint.dibujando = false;
    paint.ultimoX = -1;
    paint.ultimoY = -1;

    tft.fillScreen(C_FONDO_PRINCIPAL);
    dibujarEncabezado("Paint");
    paintDibujarBotonesSuperiores();

    dibujarTarjeta(10, 38, 300, 145, C_PAINT_FONDO);
    tft.drawRect(10, 38, 300, 145, C_BORDE);

    for (int gx = 10; gx < 310; gx += 10) {
        for (int gy = 38; gy < 183; gy += 10) {
            tft.drawPixel(gx, gy, C_PAINT_GRID);
        }
    }

    paintDibujarPaletaColores();
    paintDibujarControles();
}

void paintDibujarPaletaColores() {
    int y = 188;
    int xInicio = 10;
    int tam = 18;
    for (int i = 0; i < NUM_COLORES_PALETA; i++) {
        int x = xInicio + i * 24;
        dibujarTarjeta(x, y, tam, tam, PALETA_COLORES[i]);
        tft.drawRect(x, y, tam, tam, C_BORDE);
        if (PALETA_COLORES[i] == paint.colorSeleccionado && !paint.borrando) {
            tft.drawRect(x - 1, y - 1, tam + 2, tam + 2, C_MARCA_CLARO);
        }
    }
}

void paintDibujarControles() {
    dibujarBoton(280, 188, 30, 18, "B", nullptr);
    if (paint.borrando) {
        tft.drawRect(279, 187, 32, 20, C_MARCA_CLARO);
    }

    int yGrosor = 212;
    tft.setTextColor(C_TEXTO_TERCIARIO);
    tft.setTextSize(1);
    tft.setCursor(10, yGrosor + 2);
    tft.print("Grosor:");

    for (int g = 1; g <= 4; g++) {
        int x = 55 + (g - 1) * 25;
        dibujarTarjeta(x, yGrosor, 20, 16, C_BOTON_INACTIVO);
        tft.drawRect(x, yGrosor, 20, 16, C_BORDE);
        if (paint.grosorPincel == g) {
            tft.fillCircle(x + 10, yGrosor + 8, g, C_TEXTO_PRINCIPAL);
        } else {
            tft.fillCircle(x + 10, yGrosor + 8, g, C_TEXTO_TERCIARIO);
        }
    }

}

void manejarTouchPaint(int x, int y) {
    if (manejarBotonVolverUniversal(x, y)) return;

    if (enRectangulo(x, y, BTN_PAINT_LIMPIAR_X, BTN_PAINT_LIMPIAR_Y, BTN_PAINT_LIMPIAR_W, BTN_PAINT_LIMPIAR_H)) {
        beepBoton();
        dibujarTarjeta(10, 38, 300, 145, C_PAINT_FONDO);
        tft.drawRect(10, 38, 300, 145, C_BORDE);
        for (int gx = 10; gx < 310; gx += 10) {
            for (int gy = 38; gy < 183; gy += 10) {
                tft.drawPixel(gx, gy, C_PAINT_GRID);
            }
        }
        dibujarToast("Lienzo limpiado", C_TOAST_INFO, 1000);
        return;
    }

    if (enRectangulo(x, y, BTN_PAINT_GUARDAR_X, BTN_PAINT_GUARDAR_Y, BTN_PAINT_GUARDAR_W, BTN_PAINT_GUARDAR_H)) {
        beepBoton();
        dibujarToast("Captura no disponible", C_ADVERTENCIA, 1500);
        return;
    }

    if (y >= 232) {
        paint.dibujando = false;
        paint.ultimoX = -1;
        return;
    }

    if (enRectangulo(x, y, 10, 38, 300, 145)) {
        paint.dibujando = true;
        if (paint.ultimoX >= 0 && paint.ultimoY >= 0) {
            uint16_t color = paint.borrando ? C_PAINT_FONDO : paint.colorSeleccionado;
            int grosor = paint.borrando ? paint.grosorPincel * 2 : paint.grosorPincel;
            tft.drawLine(paint.ultimoX, paint.ultimoY, x, y, color);
            for (int r = 1; r <= grosor; r++) {
                tft.fillCircle(x, y, r, color);
                tft.fillCircle(paint.ultimoX, paint.ultimoY, r, color);
            }
        }
        paint.ultimoX = x;
        paint.ultimoY = y;
        return;
    } else {
        paint.dibujando = false;
        paint.ultimoX = -1;
        paint.ultimoY = -1;
    }

    if (enRectangulo(x, y, 10, 188, NUM_COLORES_PALETA * 24, 18)) {
        int idx = (x - 10) / 24;
        if (idx >= 0 && idx < NUM_COLORES_PALETA) {
            beepBoton();
            paint.colorSeleccionado = PALETA_COLORES[idx];
            paint.borrando = false;
            paintDibujarPaletaColores();
            paintDibujarControles();
        }
        return;
    }

    if (enRectangulo(x, y, 280, 188, 30, 18)) {
        beepBoton();
        paint.borrando = !paint.borrando;
        paintDibujarPaletaColores();
        paintDibujarControles();
        return;
    }

    if (enRectangulo(x, y, 55, 212, 100, 16)) {
        int idx = (x - 55) / 25;
        if (idx >= 0 && idx < 4) {
            beepBoton();
            paint.grosorPincel = idx + 1;
            paintDibujarControles();
        }
        return;
    }
}

void renderizarConfiguracion() {
    pantallaActual = PANT_CONFIG;
    tft.fillScreen(C_FONDO_PRINCIPAL);
    dibujarEncabezado("Configuracion");

    int y = 42;

    dibujarInterruptor(10, y, config.sonidoActivo, "Sonido");
    y += 30;

    dibujarInterruptor(10, y, config.screensaverActivo, "Salvapantallas");
    y += 30;

    dibujarDeslizador(10, y, 200, config.brilloPantalla, 255, "Brillo");
    y += 45;

    dibujarBoton(10, y, 145, 36, "GUARDAR", "Guardar en SD");
    dibujarBoton(165, y, 145, 36, "RESTABLECER", "Valores fabrica");

    y += 50;

    tft.setTextColor(C_TEXTO_TERCIARIO);
    tft.setTextSize(1);
    tft.setCursor(12, y);
    tft.print("Config guardada en: /luvian.cfg");
}

void dibujarInterruptor(int x, int y, bool activo, const char* etiqueta) {
    tft.setTextColor(C_TEXTO_PRINCIPAL);
    tft.setTextSize(1);
    tft.setCursor(x, y + 4);
    tft.print(etiqueta);

    int ix = x + 100;
    dibujarTarjeta(ix, y, 40, 18, activo ? C_EXITO : C_ERROR);
    tft.drawRect(ix, y, 40, 18, C_BORDE);

    if (activo) {
        tft.fillCircle(ix + 30, y + 9, 7, C_TEXTO_PRINCIPAL);
    } else {
        tft.fillCircle(ix + 10, y + 9, 7, C_TEXTO_PRINCIPAL);
    }

    tft.setTextColor(activo ? C_EXITO : C_ERROR);
    tft.setCursor(ix + 50, y + 4);
    tft.print(activo ? "ON" : "OFF");
}

void dibujarDeslizador(int x, int y, int w, int valor, int maxVal, const char* etiqueta) {
    tft.setTextColor(C_TEXTO_PRINCIPAL);
    tft.setTextSize(1);
    tft.setCursor(x, y);
    tft.print(etiqueta);

    int barraY = y + 14;
    tft.drawRect(x, barraY, w, 10, C_BORDE);
    tft.fillRect(x + 1, barraY + 1, w - 2, 8, C_FONDO_SECUNDARIO);

    int anchoRelleno = map(valor, 0, maxVal, 0, w - 2);
    tft.fillRect(x + 1, barraY + 1, anchoRelleno, 8, C_MARCA_PRIMARIO);

    tft.setTextColor(C_TEXTO_SECUNDARIO);
    tft.setCursor(x + w + 10, barraY);
    tft.print(map(valor, 0, maxVal, 0, 100));
    tft.print("%");
}

void manejarTouchConfiguracion(int x, int y) {
    if (manejarBotonVolverUniversal(x, y)) {
        guardarConfiguracionSD();
        return;
    }

    if (enRectangulo(x, y, 110, 42, 40, 18)) {
        beepBoton();
        config.sonidoActivo = !config.sonidoActivo;
        renderizarConfiguracion();
        return;
    }

    if (enRectangulo(x, y, 110, 72, 40, 18)) {
        beepBoton();
        config.screensaverActivo = !config.screensaverActivo;
        renderizarConfiguracion();
        return;
    }

    if (enRectangulo(x, y, 10, 116, 210, 14)) {
        int nuevoBrillo = map(constrain(x - 10, 0, 200), 0, 200, 0, 255);
        config.brilloPantalla = nuevoBrillo;
        renderizarConfiguracion();
        return;
    }

    if (enRectangulo(x, y, 10, 152, 145, 36)) {
        beepBoton();
        guardarConfiguracionSD();
        dibujarToast("Configuracion guardada", C_TOAST_EXITO, 2000);
        return;
    }

    if (enRectangulo(x, y, 165, 152, 145, 36)) {
        beepBoton();
        config.sonidoActivo = true;
        config.brilloPantalla = 255;
        config.screensaverActivo = true;
        config.temaColor = 0;
        renderizarConfiguracion();
        dibujarToast("Valores restablecidos", C_TOAST_INFO, 1500);
        return;
    }
}

void renderizarMemoria() {
    pantallaActual = PANT_MEMORIA;
    tft.fillScreen(C_FONDO_PRINCIPAL);
    dibujarEncabezado("Gestor de Memoria");
    actualizarMemoriaDisplay();
}

void actualizarMemoriaDisplay() {
    tft.fillRect(8, 38, 304, 160, C_FONDO_PRINCIPAL);

    uint32_t libre = obtenerMemoriaLibre();
    uint32_t total = obtenerMemoriaTotal();
    uint32_t usada = total - libre;
    int porcentaje = (usada * 100) / total;

    dibujarTarjeta(10, 42, 300, 60, C_FONDO_SECUNDARIO);
    tft.drawRect(10, 42, 300, 60, C_BORDE);

    tft.setTextColor(C_TEXTO_SECUNDARIO);
    tft.setTextSize(1);
    tft.setCursor(18, 48);
    tft.print("RAM DISPONIBLE");

    char buf[16];
    formatearBytes(libre, buf, sizeof(buf));
    tft.setTextColor(C_MARCA_PRIMARIO);
    tft.setTextSize(2);
    tft.setCursor(18, 62);
    tft.print(buf);

    tft.setTextColor(C_TEXTO_TERCIARIO);
    tft.setTextSize(1);
    tft.setCursor(130, 62);
    tft.print("de ");
    formatearBytes(total, buf, sizeof(buf));
    tft.print(buf);

    dibujarBarraProgreso(15, 92, 290, 12, porcentaje, 100,
        porcentaje > 90 ? C_ERROR : porcentaje > 70 ? C_ADVERTENCIA : C_EXITO);

    tft.setTextColor(C_TEXTO_TERCIARIO);
    tft.setTextSize(1);
    tft.setCursor(15, 108);
    tft.print("Uso: ");
    tft.print(porcentaje);
    tft.print("%");

    int y = 118;
    dibujarFilaMemoria("Heap libre:", libre, y);
    y += 16;
    dibujarFilaMemoria("Heap usado:", usada, y);
    y += 16;
    dibujarFilaMemoria("Heap total:", total, y);
    y += 16;
    dibujarFilaMemoria("Minimo libre:", ESP.getMinFreeHeap(), y);
    y += 16;
    dibujarFilaMemoria("Tamaño maximo bloque:", ESP.getMaxAllocHeap(), y);
}

void dibujarFilaMemoria(const char* etiqueta, uint32_t valor, int y) {
    tft.setTextColor(C_TEXTO_SECUNDARIO);
    tft.setTextSize(1);
    tft.setCursor(12, y);
    tft.print(etiqueta);
    char buf[16];
    formatearBytes(valor, buf, sizeof(buf));
    tft.setTextColor(C_TEXTO_PRINCIPAL);
    tft.setCursor(140, y);
    tft.print(buf);
}

// ==================== PONG MEJORADO ====================

void iniciarPong() {
    pantallaActual = PANT_PONG;
    juego.juegoSeleccionado = 1;
    juego.gameOver = false;
    juego.victoria = false;
    juego.ultimoFrame = millis();
    juego.sonidoActivo = false;
    juego.activo = true;
    juego.pausado = false;

    int velInicialBola = (juego.pongDificultad == 0) ? 2 : PONG_VEL_BOLA;
    int velCpu = (juego.pongDificultad == 0) ? 3 : PONG_VEL_CPU;

    juego.paletaJugadorY = (PONG_AREA_ALTO - PONG_PALETA_ALTO) / 2;
    juego.paletaCpuY = (PONG_AREA_ALTO - PONG_PALETA_ALTO) / 2;
    juego.bolaX = PONG_AREA_X + PONG_AREA_ANCHO / 2;
    juego.bolaY = PONG_AREA_Y + PONG_AREA_ALTO / 2;
    juego.bolaVelX = (random(0, 2) == 0) ? velInicialBola : -velInicialBola;
    juego.bolaVelY = (random(0, 2) == 0) ? 2 : -2;
    juego.velCpu = velCpu;
    juego.puntosJugador = 0;
    juego.puntosCpu = 0;

    renderizarPong();
}

void renderizarCampoPong() {
    tft.fillRect(PONG_AREA_X, PONG_AREA_Y, PONG_AREA_ANCHO, PONG_AREA_ALTO, C_PONG_FONDO);
    tft.drawRect(PONG_AREA_X, PONG_AREA_Y, PONG_AREA_ANCHO, PONG_AREA_ALTO, C_PONG_CAMPO);

    int centroX = PONG_AREA_X + PONG_AREA_ANCHO / 2;
    for (int y = PONG_AREA_Y + 4; y < PONG_AREA_Y + PONG_AREA_ALTO - 4; y += 12) {
        tft.drawFastVLine(centroX, y, 6, C_PONG_LINEA);
    }
}

void dibujarPaletaPong(int x, int y, uint16_t color) {
    tft.fillRect(x, y, PONG_PALETA_ANCHO, PONG_PALETA_ALTO, color);
    tft.drawFastVLine(x, y, PONG_PALETA_ALTO, C_MARCA_CLARO);
    tft.drawFastVLine(x + PONG_PALETA_ANCHO - 1, y, PONG_PALETA_ALTO, C_FONDO_PRINCIPAL);
}

void borrarPaletaPong(int x, int y) {
    tft.fillRect(x, y, PONG_PALETA_ANCHO, PONG_PALETA_ALTO, C_PONG_FONDO);
}

void dibujarBolaPong(int x, int y) {
    tft.fillCircle(x, y, PONG_BOLA_RADIO + 2, C_PONG_BOLA_RASTRO);
    tft.fillCircle(x, y, PONG_BOLA_RADIO, C_PONG_BOLA);
}

void borrarBolaPong(int x, int y) {
    int r = PONG_BOLA_RADIO + 2;
    tft.fillRect(x - r, y - r, r * 2 + 1, r * 2 + 1, C_PONG_FONDO);

    int centroX = PONG_AREA_X + PONG_AREA_ANCHO / 2;
    if (x - r <= centroX && x + r >= centroX) {
        for (int ly = y - r; ly <= y + r; ly += 12) {
            if (ly >= PONG_AREA_Y + 4 && ly < PONG_AREA_Y + PONG_AREA_ALTO - 4) {
                tft.drawFastVLine(centroX, ly, 6, C_PONG_LINEA);
            }
        }
    }

    if (x - r <= PONG_AREA_X + 2 || x + r >= PONG_AREA_X + PONG_AREA_ANCHO - 2 ||
        y - r <= PONG_AREA_Y + 2 || y + r >= PONG_AREA_Y + PONG_AREA_ALTO - 2) {
        tft.drawRect(PONG_AREA_X, PONG_AREA_Y, PONG_AREA_ANCHO, PONG_AREA_ALTO, C_PONG_CAMPO);
    }
}

void dibujarMarcadorPong() {
    tft.fillRect(PONG_AREA_X + 60, PONG_AREA_Y - 28, PONG_AREA_ANCHO - 120, 22, C_FONDO_PRINCIPAL);

    tft.setTextSize(2);
    tft.setTextColor(C_PONG_MARCADOR);

    char buf[4];
    sprintf(buf, "%d", juego.puntosJugador);
    int anchoTexto = strlen(buf) * 12;
    tft.setCursor(PONG_AREA_X + PONG_AREA_ANCHO / 2 - 22 - anchoTexto, PONG_AREA_Y - 26);
    tft.print(buf);

    tft.setCursor(PONG_AREA_X + PONG_AREA_ANCHO / 2 - 6, PONG_AREA_Y - 26);
    tft.print("-");

    sprintf(buf, "%d", juego.puntosCpu);
    tft.setCursor(PONG_AREA_X + PONG_AREA_ANCHO / 2 + 14, PONG_AREA_Y - 26);
    tft.print(buf);
}

void renderizarPong() {
    tft.fillScreen(C_FONDO_PRINCIPAL);

    tft.fillRect(0, 0, ANCHO_PANTALLA, 30, C_FONDO_SECUNDARIO);
    dibujarBotonVolverUniversal();
    tft.setTextColor(C_MARCA_PRIMARIO);
    tft.setTextSize(1);
    tft.setCursor(BTN_VOLVER_U_X + BTN_VOLVER_U_W + 8, 11);
    tft.print("PONG  |  Desliza para controlar");
    tft.drawFastHLine(0, 30, ANCHO_PANTALLA, C_BORDE_ACTIVO);

    renderizarCampoPong();
    dibujarMarcadorPong();

    dibujarPaletaPong(PONG_PALETA_J_X, PONG_AREA_Y + juego.paletaJugadorY, C_PONG_PALETA_J);
    dibujarPaletaPong(PONG_PALETA_CPU_X, PONG_AREA_Y + juego.paletaCpuY, C_PONG_PALETA_CPU);

    dibujarBolaPong(juego.bolaX, juego.bolaY);
}

void renderizarGameOverPong() {
    tft.fillRect(PONG_AREA_X + 20, PONG_AREA_Y + 30, PONG_AREA_ANCHO - 40, PONG_AREA_ALTO - 60, C_FONDO_PRINCIPAL);
    tft.drawRect(PONG_AREA_X + 20, PONG_AREA_Y + 30, PONG_AREA_ANCHO - 40, PONG_AREA_ALTO - 60, C_BORDE_ACTIVO);

    tft.setTextSize(2);
    if (juego.victoria) {
        tft.setTextColor(C_EXITO);
        tft.setCursor(PONG_AREA_X + 65, PONG_AREA_Y + 50);
        tft.print("VICTORIA");
    } else {
        tft.setTextColor(C_ERROR);
        tft.setCursor(PONG_AREA_X + 65, PONG_AREA_Y + 50);
        tft.print("DERROTA");
    }

    tft.setTextSize(1);
    tft.setTextColor(C_TEXTO_SECUNDARIO);
    tft.setCursor(PONG_AREA_X + 55, PONG_AREA_Y + 80);
    tft.print("Toca para volver al menu");

    if (config.sonidoActivo) {
        if (juego.victoria) {
            tone(PIN_BUZZER, 523, 200); delay(250);
            tone(PIN_BUZZER, 659, 200); delay(250);
            tone(PIN_BUZZER, 784, 300); delay(350);
        } else {
            tone(PIN_BUZZER, 300, 400); delay(450);
            tone(PIN_BUZZER, 200, 600); delay(650);
        }
        noTone(PIN_BUZZER);
    }
}

void sonidoRebotePong() {
    sonidoEfecto(800, 30);
}

void sonidoPuntoPong() {
    sonidoEfecto(1200, 100);
}

void actualizarCpuPong() {
    int centroCpu = juego.paletaCpuY + PONG_PALETA_ALTO / 2;
    int centroBola = juego.bolaY - PONG_AREA_Y;

    if (centroCpu < centroBola - 8) {
        juego.paletaCpuY += juego.velCpu;
    } else if (centroCpu > centroBola + 8) {
        juego.paletaCpuY -= juego.velCpu;
    }

    juego.paletaCpuY = constrain(juego.paletaCpuY, 0, PONG_AREA_ALTO - PONG_PALETA_ALTO);
}

void moverBolaPong() {
    int bolaXAnterior = juego.bolaX;
    int bolaYAnterior = juego.bolaY;

    juego.bolaX += juego.bolaVelX;
    juego.bolaY += juego.bolaVelY;

    if (juego.bolaY <= PONG_AREA_Y + PONG_BOLA_RADIO) {
        juego.bolaY = PONG_AREA_Y + PONG_BOLA_RADIO + 1;
        juego.bolaVelY = abs(juego.bolaVelY);
        sonidoRebotePong();
    } else if (juego.bolaY >= PONG_AREA_Y + PONG_AREA_ALTO - PONG_BOLA_RADIO) {
        juego.bolaY = PONG_AREA_Y + PONG_AREA_ALTO - PONG_BOLA_RADIO - 1;
        juego.bolaVelY = -abs(juego.bolaVelY);
        sonidoRebotePong();
    }

    // === REBOTE JUGADOR - FISICA MEJORADA ===
    if (juego.bolaX <= PONG_PALETA_J_X + PONG_PALETA_ANCHO + PONG_BOLA_RADIO &&
        juego.bolaX >= PONG_PALETA_J_X - PONG_BOLA_RADIO &&
        juego.bolaY >= PONG_AREA_Y + juego.paletaJugadorY - PONG_BOLA_RADIO &&
        juego.bolaY <= PONG_AREA_Y + juego.paletaJugadorY + PONG_PALETA_ALTO + PONG_BOLA_RADIO) {

        if (juego.bolaVelX < 0) {
            juego.bolaVelX = -juego.bolaVelX;

            int centroPaleta = PONG_AREA_Y + juego.paletaJugadorY + PONG_PALETA_ALTO / 2;
            float impactoRel = (float)(juego.bolaY - centroPaleta) / (PONG_PALETA_ALTO / 2.0f);
            float velTotal = abs(juego.bolaVelX);
            if (velTotal < 2.0f) velTotal = 3.0f;

            float nuevaVelY = impactoRel * (velTotal * 0.9f);
            if (nuevaVelY > 6.0f) nuevaVelY = 6.0f;
            if (nuevaVelY < -6.0f) nuevaVelY = -6.0f;
            if (nuevaVelY > -1.0f && nuevaVelY < 1.0f) nuevaVelY = (impactoRel >= 0) ? 1.0f : -1.0f;
            juego.bolaVelY = (int8_t)nuevaVelY;

            int maxVel = (juego.pongDificultad == 0) ? 5 : 7;
            if (abs(juego.bolaVelX) < maxVel) juego.bolaVelX++;
            sonidoRebotePong();
        }
    }

    // === REBOTE CPU - FISICA MEJORADA ===
    if (juego.bolaX >= PONG_PALETA_CPU_X - PONG_BOLA_RADIO &&
        juego.bolaX <= PONG_PALETA_CPU_X + PONG_PALETA_ANCHO + PONG_BOLA_RADIO &&
        juego.bolaY >= PONG_AREA_Y + juego.paletaCpuY - PONG_BOLA_RADIO &&
        juego.bolaY <= PONG_AREA_Y + juego.paletaCpuY + PONG_PALETA_ALTO + PONG_BOLA_RADIO) {

        if (juego.bolaVelX > 0) {
            juego.bolaVelX = -juego.bolaVelX;

            int centroPaleta = PONG_AREA_Y + juego.paletaCpuY + PONG_PALETA_ALTO / 2;
            float impactoRel = (float)(juego.bolaY - centroPaleta) / (PONG_PALETA_ALTO / 2.0f);
            float velTotal = abs(juego.bolaVelX);
            if (velTotal < 2.0f) velTotal = 3.0f;

            float nuevaVelY = impactoRel * (velTotal * 0.9f);
            if (nuevaVelY > 6.0f) nuevaVelY = 6.0f;
            if (nuevaVelY < -6.0f) nuevaVelY = -6.0f;
            if (nuevaVelY > -1.0f && nuevaVelY < 1.0f) nuevaVelY = (impactoRel >= 0) ? 1.0f : -1.0f;
            juego.bolaVelY = (int8_t)nuevaVelY;

            int maxVel = (juego.pongDificultad == 0) ? 5 : 7;
            if (abs(juego.bolaVelX) < maxVel) juego.bolaVelX--;
            sonidoRebotePong();
        }
    }

    static int ultimaBolaX = 0;
    static unsigned long timerAtascada = 0;
    if (abs(juego.bolaX - ultimaBolaX) < 2) {
        if (timerAtascada == 0) timerAtascada = millis();
        else if (millis() - timerAtascada > 2000) {
            juego.bolaVelY = (juego.bolaVelY > 0) ? 3 : -3;
            juego.bolaVelX = (juego.bolaVelX > 0) ? 4 : -4;
            timerAtascada = 0;
        }
    } else {
        timerAtascada = 0;
    }
    ultimaBolaX = juego.bolaX;

    if (juego.bolaX < PONG_AREA_X + PONG_BOLA_RADIO) {
        juego.puntosCpu++;
        sonidoPuntoPong();
        timerAtascada = 0;
        if (juego.puntosCpu >= PONG_PUNTOS_VICTORIA) {
            juego.gameOver = true;
            juego.victoria = false;
            renderizarGameOverPong();
            return;
        }
        resetearBolaPong();
    }

    if (juego.bolaX > PONG_AREA_X + PONG_AREA_ANCHO - PONG_BOLA_RADIO) {
        juego.puntosJugador++;
        sonidoPuntoPong();
        timerAtascada = 0;
        if (juego.puntosJugador >= PONG_PUNTOS_VICTORIA) {
            juego.gameOver = true;
            juego.victoria = true;
            renderizarGameOverPong();
            return;
        }
        resetearBolaPong();
    }

    if (bolaXAnterior != juego.bolaX || bolaYAnterior != juego.bolaY) {
        borrarBolaPong(bolaXAnterior, bolaYAnterior);
        dibujarBolaPong(juego.bolaX, juego.bolaY);
    }
    dibujarMarcadorPong();
}

void resetearBolaPong() {
    delay(500);
    borrarBolaPong(juego.bolaX, juego.bolaY);
    juego.bolaX = PONG_AREA_X + PONG_AREA_ANCHO / 2;
    juego.bolaY = PONG_AREA_Y + PONG_AREA_ALTO / 2;
    int velInicial = (juego.pongDificultad == 0) ? 2 : PONG_VEL_BOLA;
    juego.bolaVelX = (random(0, 2) == 0) ? velInicial : -velInicial;
    int opcionesVelY[] = {-3, -2, 2, 3};
    juego.bolaVelY = opcionesVelY[random(0, 4)];
    dibujarBolaPong(juego.bolaX, juego.bolaY);
}

void actualizarJugadorTouchPong(int touchY) {
    int nuevaY = touchY - PONG_AREA_Y - PONG_PALETA_ALTO / 2;
    nuevaY = constrain(nuevaY, 0, PONG_AREA_ALTO - PONG_PALETA_ALTO);

    if (nuevaY != juego.paletaJugadorY) {
        borrarPaletaPong(PONG_PALETA_J_X, PONG_AREA_Y + juego.paletaJugadorY);
        juego.paletaJugadorY = nuevaY;
        dibujarPaletaPong(PONG_PALETA_J_X, PONG_AREA_Y + juego.paletaJugadorY, C_PONG_PALETA_J);
    }
}

void procesarPong() {
    unsigned long ahora = millis();

    if (ahora - juego.ultimoFrame < PONG_FPS_MS) {
        int x, y;
        if (obtenerTouchDirecto(x, y)) {
            reiniciarActividad();
            if (touchEnBotonVolver(x, y)) {
                beepBoton();
                renderizarMenu();
                return;
            }
            if (juego.gameOver) {
                beepBoton();
                renderizarMenuJuegos();
                return;
            }
            if (y >= PONG_AREA_Y && y < PONG_AREA_Y + PONG_AREA_ALTO) {
                actualizarJugadorTouchPong(y);
            }
        }
        return;
    }

    juego.ultimoFrame = ahora;

    if (juego.gameOver) {
        int x, y;
        if (obtenerTouchDirecto(x, y)) {
            reiniciarActividad();
            if (touchEnBotonVolver(x, y)) {
                beepBoton();
                renderizarMenu();
                return;
            }
            beepBoton();
            renderizarMenuJuegos();
        }
        return;
    }

    int cpuYAnterior = juego.paletaCpuY;
    actualizarCpuPong();
    if (cpuYAnterior != juego.paletaCpuY) {
        borrarPaletaPong(PONG_PALETA_CPU_X, PONG_AREA_Y + cpuYAnterior);
        dibujarPaletaPong(PONG_PALETA_CPU_X, PONG_AREA_Y + juego.paletaCpuY, C_PONG_PALETA_CPU);
    }

    moverBolaPong();

    int x, y;
    if (obtenerTouchDirecto(x, y)) {
        reiniciarActividad();
        if (touchEnBotonVolver(x, y)) {
            beepBoton();
            renderizarMenu();
            return;
        }
        if (y >= PONG_AREA_Y && y < PONG_AREA_Y + PONG_AREA_ALTO) {
            actualizarJugadorTouchPong(y);
        }
    }

    // === CORRECCION: Redibujar paletas cada frame para evitar que la bola las dañe ===
    dibujarPaletaPong(PONG_PALETA_J_X, PONG_AREA_Y + juego.paletaJugadorY, C_PONG_PALETA_J);
    dibujarPaletaPong(PONG_PALETA_CPU_X, PONG_AREA_Y + juego.paletaCpuY, C_PONG_PALETA_CPU);

    if (juego.sonidoActivo && (ahora - juego.inicioSonido >= 50)) {
        noTone(PIN_BUZZER);
        juego.sonidoActivo = false;
    }
}

// ==================== SPACE INVADERS MEJORADO ====================

const uint8_t SPRITE_NAVE[12][20] = {
    {0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,0,1,1,0,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,0,1,1,1,1,0,1,1,0,0,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
    {0,0,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,0,0},
    {0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0},
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}
};

const uint8_t SPRITE_ALIEN1[12][18] = {
    {0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,1,1,0,1,1,1,1,0,1,1,0,0,0,0},
    {0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0},
    {0,0,1,1,0,0,0,1,1,1,1,0,0,0,1,1,0,0},
    {0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0},
    {1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1},
    {0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
    {0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0},
    {0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0}
};

const uint8_t SPRITE_ALIEN2[12][18] = {
    {0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,0},
    {0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0},
    {0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0},
    {1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1},
    {0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0},
    {0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0},
    {0,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0}
};

const uint8_t SPRITE_ALIEN3[12][18] = {
    {0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,0,1,1,0,1,1,0,0,0,0,0},
    {0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
    {0,0,1,1,0,0,0,1,1,1,1,0,0,0,1,1,0,0},
    {0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0},
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0}
};

void dibujarSprite(const uint8_t sprite[][18], int x, int y, int ancho, int alto, uint16_t color, uint16_t colorFondo) {
    for (int fila = 0; fila < alto; fila++) {
        for (int col = 0; col < ancho; col++) {
            if (sprite[fila][col] == 1) {
                tft.drawPixel(x + col, y + fila, color);
            } else {
                tft.drawPixel(x + col, y + fila, colorFondo);
            }
        }
    }
}

void dibujarSpriteNave(const uint8_t sprite[][20], int x, int y, int ancho, int alto, uint16_t color, uint16_t colorMotor, uint16_t colorFondo) {
    for (int fila = 0; fila < alto; fila++) {
        for (int col = 0; col < ancho; col++) {
            if (sprite[fila][col] == 1) {
                if (fila >= 9) {
                    tft.drawPixel(x + col, y + fila, colorMotor);
                } else {
                    tft.drawPixel(x + col, y + fila, color);
                }
            } else {
                tft.drawPixel(x + col, y + fila, colorFondo);
            }
        }
    }
}

void dibujarNaveEspacial(int x, int y, uint16_t color, uint16_t colorMotor) {
    dibujarSpriteNave(SPRITE_NAVE, x, y, SI_NAVE_ANCHO, SI_NAVE_ALTO, color, colorMotor, C_PONG_FONDO);
}

void borrarNaveEspacial(int x, int y) {
    tft.fillRect(x, y, SI_NAVE_ANCHO, SI_NAVE_ALTO, C_PONG_FONDO);
}

void dibujarAlienNave(int x, int y, uint8_t tipo, uint16_t color) {
    switch (tipo % 3) {
        case 0: dibujarSprite(SPRITE_ALIEN1, x, y, 18, 12, color, C_PONG_FONDO); break;
        case 1: dibujarSprite(SPRITE_ALIEN2, x, y, 18, 12, color, C_PONG_FONDO); break;
        case 2: dibujarSprite(SPRITE_ALIEN3, x, y, 18, 12, color, C_PONG_FONDO); break;
    }
}

void borrarAlienNave(int x, int y) {
    tft.fillRect(x, y, SI_ALIEN_ANCHO, SI_ALIEN_ALTO, C_PONG_FONDO);
}

void dibujarEstrellasFondo() {
    static bool estrellasDibujadas = false;
    if (!estrellasDibujadas) {
        estrellasDibujadas = true;
        for (int i = 0; i < 30; i++) {
            int ex = PONG_AREA_X + random(4, PONG_AREA_ANCHO - 4);
            int ey = PONG_AREA_Y + random(4, PONG_AREA_ALTO - 4);
            tft.drawPixel(ex, ey, C_SI_ESTRELLA);
            if (random(0, 3) == 0) {
                tft.drawPixel(ex + 1, ey, C_SI_ESTRELLA);
                tft.drawPixel(ex, ey + 1, C_SI_ESTRELLA);
            }
        }
    }
}

void dibujarExplosion(int x, int y) {
    for (int i = 0; i < 8; i++) {
        int px = x + random(-6, 7);
        int py = y + random(-6, 7);
        tft.fillRect(px, py, 2, 2, C_ADVERTENCIA);
    }
    delay(20);
    for (int i = 0; i < 8; i++) {
        int px = x + random(-8, 9);
        int py = y + random(-8, 9);
        tft.fillRect(px, py, 2, 2, C_ERROR);
    }
    delay(20);
    tft.fillRect(x - 10, y - 10, 20, 20, C_PONG_FONDO);
}

void dibujarFondoJuego(const char* titulo) {
    tft.fillScreen(C_FONDO_PRINCIPAL);
    tft.fillRect(0, 0, ANCHO_PANTALLA, 30, C_FONDO_SECUNDARIO);
    dibujarBotonVolverUniversal();
    tft.setTextColor(C_MARCA_PRIMARIO);
    tft.setTextSize(1);
    tft.setCursor(BTN_VOLVER_U_X + BTN_VOLVER_U_W + 8, 11);
    tft.print(titulo);
    tft.drawFastHLine(0, 30, ANCHO_PANTALLA, C_BORDE_ACTIVO);
    tft.fillRect(PONG_AREA_X, PONG_AREA_Y, PONG_AREA_ANCHO, PONG_AREA_ALTO, C_PONG_FONDO);
    tft.drawRect(PONG_AREA_X, PONG_AREA_Y, PONG_AREA_ANCHO, PONG_AREA_ALTO, C_PONG_CAMPO);
    dibujarEstrellasFondo();
}

void renderizarGameOverSpace() {
    tft.fillRect(PONG_AREA_X + 20, PONG_AREA_Y + 40, PONG_AREA_ANCHO - 40, 70, C_FONDO_PRINCIPAL);
    tft.drawRect(PONG_AREA_X + 20, PONG_AREA_Y + 40, PONG_AREA_ANCHO - 40, 70, C_BORDE_ACTIVO);

    tft.setTextSize(2);
    if (juego.victoria) {
        tft.setTextColor(C_EXITO);
        tft.setCursor(PONG_AREA_X + 85, PONG_AREA_Y + 55);
        tft.print("VICTORIA");
    } else {
        tft.setTextColor(C_ERROR);
        tft.setCursor(PONG_AREA_X + 80, PONG_AREA_Y + 55);
        tft.print("GAME OVER");
    }

    tft.setTextSize(1);
    tft.setTextColor(C_TEXTO_SECUNDARIO);
    tft.setCursor(PONG_AREA_X + 65, PONG_AREA_Y + 85);
    tft.print("Toca la pantalla para salir");
}

void iniciarSpaceInvaders() {
    pantallaActual = PANT_SPACE;
    juego.juegoSeleccionado = 2;
    juego.naveX = PONG_AREA_X + PONG_AREA_ANCHO / 2 - SI_NAVE_ANCHO / 2;
    juego.balaActiva = false;
    juego.alienVelX = 2.0f; // Velocidad inicial aumentada
    juego.aliensVivos = SI_FILAS * SI_COLUMNAS;
    juego.gameOver = false;
    juego.ultimoFrame = millis();
    juego.ultimoDisparoAuto = millis();
    juego.frameAnimacion = 0;

    for (int f = 0; f < SI_FILAS; f++) {
        for (int c = 0; c < SI_COLUMNAS; c++) {
            juego.aliens[f][c].x = PONG_AREA_X + 12 + c * (SI_ALIEN_ANCHO + 14);
            juego.aliens[f][c].y = PONG_AREA_Y + 12 + f * (SI_ALIEN_ALTO + 10);
            juego.aliens[f][c].vivo = true;
            juego.aliens[f][c].tipo = f;
        }
    }

    dibujarFondoJuego(">> INVASORES DEL ESPACIO  |  Toca: Izq/Der");
    dibujarNaveEspacial(juego.naveX, PONG_AREA_Y + PONG_AREA_ALTO - SI_NAVE_ALTO - 4, C_SI_NAVE, C_SI_NAVE_MOTOR);
}

void loopSpaceInvaders() {
    unsigned long ahora = millis();
    if (ahora - juego.ultimoFrame < 16) return; // ~60 FPS (antes 30ms)
    juego.ultimoFrame = ahora;

    juego.frameAnimacion = (juego.frameAnimacion + 1) % 4;

    if (juego.gameOver) {
        int x, y;
        if (obtenerTouchDirecto(x, y)) {
            reiniciarActividad();
            if (touchEnBotonVolver(x, y)) {
                beepBoton();
                renderizarMenu();
                return;
            }
            beepBoton();
            renderizarMenuJuegos();
        }
        return;
    }

    // === BALA MAS RAPIDA ===
    if (juego.balaActiva) {
        tft.fillRect(juego.balaX, juego.balaY, 2, 6, C_PONG_FONDO);
        juego.balaY -= 8; // antes 5
        if (juego.balaY < PONG_AREA_Y + 2) {
            juego.balaActiva = false;
        } else {
            tft.fillRect(juego.balaX, juego.balaY, 2, 4, C_SI_BALA);
            tft.fillRect(juego.balaX, juego.balaY + 4, 2, 2, C_MARCA_CLARO);
        }
    } else if (ahora - juego.ultimoDisparoAuto > 500) { // antes 800ms
        juego.balaX = juego.naveX + SI_NAVE_ANCHO / 2;
        juego.balaY = PONG_AREA_Y + PONG_AREA_ALTO - SI_NAVE_ALTO - 8;
        juego.balaActiva = true;
        juego.ultimoDisparoAuto = ahora;
        sonidoEfecto(1800, 20);
    }

    bool cambiarDireccion = false;
    for (int f = 0; f < SI_FILAS; f++) {
        for (int c = 0; c < SI_COLUMNAS; c++) {
            if (juego.aliens[f][c].vivo) {
                if ((juego.aliens[f][c].x + juego.alienVelX <= PONG_AREA_X + 2) ||
                    (juego.aliens[f][c].x + SI_ALIEN_ANCHO + juego.alienVelX >= PONG_AREA_X + PONG_AREA_ANCHO - 2)) {
                    cambiarDireccion = true;
                }
            }
        }
    }

    if (cambiarDireccion) {
        juego.alienVelX = -juego.alienVelX;
        // Acelerar progresivamente cada vez que bajan
        if (juego.alienVelX > 0) juego.alienVelX += 0.15f;
        else juego.alienVelX -= 0.15f;
        if (abs(juego.alienVelX) > 4.0f) {
            juego.alienVelX = (juego.alienVelX > 0) ? 4.0f : -4.0f;
        }

        for (int f = 0; f < SI_FILAS; f++) {
            for (int c = 0; c < SI_COLUMNAS; c++) {
                if (juego.aliens[f][c].vivo) {
                    borrarAlienNave(juego.aliens[f][c].x, juego.aliens[f][c].y);
                    juego.aliens[f][c].y += 6;
                    if (juego.aliens[f][c].y + SI_ALIEN_ALTO >= PONG_AREA_Y + PONG_AREA_ALTO - SI_NAVE_ALTO - 4) {
                        juego.gameOver = true;
                        juego.victoria = false;
                        renderizarGameOverSpace();
                        return;
                    }
                }
            }
        }
    } else {
        for (int f = 0; f < SI_FILAS; f++) {
            for (int c = 0; c < SI_COLUMNAS; c++) {
                if (juego.aliens[f][c].vivo) {
                    borrarAlienNave(juego.aliens[f][c].x, juego.aliens[f][c].y);
                    juego.aliens[f][c].x += juego.alienVelX;

                    uint16_t colorAlien;
                    switch (juego.aliens[f][c].tipo % 3) {
                        case 0: colorAlien = C_SI_ALIEN1; break;
                        case 1: colorAlien = C_SI_ALIEN2; break;
                        case 2: colorAlien = C_SI_ALIEN3; break;
                        default: colorAlien = C_SI_ALIEN1;
                    }
                    dibujarAlienNave(juego.aliens[f][c].x, juego.aliens[f][c].y, juego.aliens[f][c].tipo, colorAlien);
                }
            }
        }
    }

    if (juego.balaActiva) {
        for (int f = 0; f < SI_FILAS; f++) {
            for (int c = 0; c < SI_COLUMNAS; c++) {
                if (juego.aliens[f][c].vivo) {
                    if (juego.balaX >= juego.aliens[f][c].x && juego.balaX <= juego.aliens[f][c].x + SI_ALIEN_ANCHO &&
                        juego.balaY >= juego.aliens[f][c].y && juego.balaY <= juego.aliens[f][c].y + SI_ALIEN_ALTO) {

                        dibujarExplosion(juego.aliens[f][c].x + SI_ALIEN_ANCHO / 2, juego.aliens[f][c].y + SI_ALIEN_ALTO / 2);
                        tft.fillRect(juego.balaX, juego.balaY, 2, 6, C_PONG_FONDO);
                        juego.aliens[f][c].vivo = false;
                        juego.balaActiva = false;
                        juego.aliensVivos--;
                        sonidoEfecto(400, 40);

                        if (juego.aliensVivos == 0) {
                            juego.gameOver = true;
                            juego.victoria = true;
                            renderizarGameOverSpace();
                            return;
                        }
                        break;
                    }
                }
            }
            if (!juego.balaActiva) break;
        }
    }

    // === NAVE CON MOVIMIENTO FLUIDO Y DIRECTO ===
    int tx, ty;
    if (obtenerTouchDirecto(tx, ty)) {
        reiniciarActividad();
        if (touchEnBotonVolver(tx, ty)) {
            beepBoton();
            renderizarMenu();
            return;
        }
        if (ty > 160) {
            int targetX = tx - SI_NAVE_ANCHO / 2;
            targetX = constrain(targetX, PONG_AREA_X + 4, PONG_AREA_X + PONG_AREA_ANCHO - SI_NAVE_ANCHO - 4);
            if (targetX != juego.naveX) {
                borrarNaveEspacial(juego.naveX, PONG_AREA_Y + PONG_AREA_ALTO - SI_NAVE_ALTO - 4);
                int diff = targetX - juego.naveX;
                if (abs(diff) > 6) {
                    juego.naveX += (diff > 0) ? 6 : -6;
                } else {
                    juego.naveX = targetX;
                }
                juego.naveX = constrain(juego.naveX, PONG_AREA_X + 4, PONG_AREA_X + PONG_AREA_ANCHO - SI_NAVE_ANCHO - 4);
                dibujarNaveEspacial(juego.naveX, PONG_AREA_Y + PONG_AREA_ALTO - SI_NAVE_ALTO - 4, C_SI_NAVE, C_SI_NAVE_MOTOR);
            }
        }
    }

    tft.drawRect(PONG_AREA_X, PONG_AREA_Y, PONG_AREA_ANCHO, PONG_AREA_ALTO, C_PONG_CAMPO);

    if (juego.sonidoActivo && (millis() - juego.inicioSonido >= 40)) {
        noTone(PIN_BUZZER);
        juego.sonidoActivo = false;
    }
}

void manejarMenuPrincipal(int x, int y) {
    if      (enRectangulo(x, y, BTN_COL1_X, BTN_FILA1_Y, BTN_ANCHO, BTN_FILA1_ALTO)) { beepBoton(); renderizarExploradorMejorado(); }
    else if (enRectangulo(x, y, BTN_COL2_X, BTN_FILA1_Y, BTN_ANCHO, BTN_FILA1_ALTO)) { beepBoton(); renderizarInfo(); }
    else if (enRectangulo(x, y, BTN_COL3_X, BTN_FILA1_Y, BTN_ANCHO, BTN_FILA1_ALTO)) { beepBoton(); renderizarTemperatura(); }
    else if (enRectangulo(x, y, BTN_COL1_X, BTN_FILA2_Y, BTN_ANCHO, BTN_FILA1_ALTO)) { beepBoton(); renderizarMenuJuegos(); }
    else if (enRectangulo(x, y, BTN_COL2_X, BTN_FILA2_Y, BTN_ANCHO, BTN_FILA1_ALTO)) { beepBoton(); renderizarCalculadora(); }
    else if (enRectangulo(x, y, BTN_COL3_X, BTN_FILA2_Y, BTN_ANCHO, BTN_FILA1_ALTO)) { beepBoton(); renderizarReloj(); }
    else if (enRectangulo(x, y, BTN_COL1_X, BTN_FILA3_Y, BTN_ANCHO, BTN_FILA1_ALTO)) { beepBoton(); renderizarPaint(); }
    else if (enRectangulo(x, y, BTN_COL2_X, BTN_FILA3_Y, BTN_ANCHO, BTN_FILA1_ALTO)) { beepBoton(); renderizarConfiguracion(); }
}

void manejarMenuJuegos(int x, int y) {
    if (manejarBotonVolverUniversal(x, y)) return;
    if      (enRectangulo(x, y, BTN_PONG_X,  BTN_JUEGO_Y, BTN_JUEGO_ANCHO, BTN_JUEGO_ALTO)) { beepBoton(); renderizarPongMenu(); }
    else if (enRectangulo(x, y, BTN_SPACE_X, BTN_JUEGO_Y, BTN_JUEGO_ANCHO, BTN_JUEGO_ALTO)) { beepBoton(); iniciarSpaceInvaders(); }
}

void dibujarBotonIcono(int x, int y, int ancho, int alto, const uint8_t* icono, uint16_t colorIcono, const char* subtitulo) {
    dibujarTarjeta(x, y, ancho, alto, C_BOTON_INACTIVO);
    tft.drawRect(x, y, ancho, alto, C_BORDE);
    tft.drawRect(x + 1, y + 1, ancho - 2, alto - 2, C_BORDE);
    tft.drawFastHLine(x + 2, y + 2, ancho - 4, C_MARCA_OSCURO);

    int iconoX = x + (ancho - 24) / 2;
    int iconoY = y + (alto - 24) / 2 - 5;
    tft.drawBitmap(iconoX, iconoY, icono, 24, 24, colorIcono);

    if (subtitulo) {
        tft.setTextColor(C_TEXTO_TERCIARIO);
        tft.setTextSize(1);
        int16_t subX = x + (ancho / 2) - (strlen(subtitulo) * 3);
        tft.setCursor(subX, y + alto - 12);
        tft.print(subtitulo);
    }
}

void dibujarEncabezado(const char* titulo) {
    tft.fillRect(0, ENCABEZADO_Y, ANCHO_PANTALLA, ENCABEZADO_ALTO, C_FONDO_SECUNDARIO);
    tft.drawFastHLine(0, 0, ANCHO_PANTALLA, C_MARCA_PRIMARIO);

    if (pantallaActual != PANT_MENU && pantallaActual != PANT_BOOT) {
        dibujarBotonVolverUniversal();
    }

    tft.drawFastHLine(0, ENCABEZADO_ALTO - 1, ANCHO_PANTALLA, C_BORDE);
}

void dibujarBoton(int x, int y, int ancho, int alto, const char* etiqueta, const char* subtitulo) {
    dibujarTarjeta(x, y, ancho, alto, C_BOTON_INACTIVO);

    tft.drawRect(x, y, ancho, alto, C_BORDE);
    tft.drawRect(x + 1, y + 1, ancho - 2, alto - 2, C_BORDE);
    tft.drawFastHLine(x + 2, y + 2, ancho - 4, C_MARCA_OSCURO);

    tft.setTextColor(C_MARCA_PRIMARIO);
    tft.setTextSize(2);
    int16_t etiquetaX = x + (ancho / 2) - (strlen(etiqueta) * 6);
    int16_t etiquetaY = y + (alto / 2) - 14;
    tft.setCursor(etiquetaX, etiquetaY);
    tft.print(etiqueta);

    if (subtitulo) {
        tft.setTextColor(C_TEXTO_TERCIARIO);
        tft.setTextSize(1);
        int16_t subX = x + (ancho / 2) - (strlen(subtitulo) * 3);
        tft.setCursor(subX, etiquetaY + 20);
        tft.print(subtitulo);
    }
}

void dibujarPanel(int x, int y, int ancho, int alto, const char* titulo) {
    tft.fillRect(x, y, ancho, alto, C_FONDO_SECUNDARIO);
    tft.drawRect(x, y, ancho, alto, C_BORDE);
    if (titulo) {
        tft.setTextColor(C_TEXTO_SECUNDARIO);
        tft.setTextSize(1);
        tft.setCursor(x + 8, y + 6);
        tft.print(titulo);
    }
}

void dibujarTarjeta(int x, int y, int ancho, int alto, uint16_t colorFondo) {
    tft.fillRect(x, y, ancho, alto, colorFondo);
}

void dibujarBarraProgreso(int x, int y, int ancho, int alto, int valor, int maxVal, uint16_t colorRelleno) {
    tft.drawRect(x, y, ancho, alto, C_BORDE);
    tft.fillRect(x + 1, y + 1, ancho - 2, alto - 2, C_FONDO_SECUNDARIO);
    if (valor > 0) {
        int anchoRelleno = map(valor, 0, maxVal, 0, ancho - 2);
        anchoRelleno = constrain(anchoRelleno, 0, ancho - 2);
        tft.fillRect(x + 1, y + 1, anchoRelleno, alto - 2, colorRelleno);
    }
}

void renderizarInfo() {
    pantallaActual = PANT_INFO;
    tft.fillScreen(C_FONDO_PRINCIPAL);

    dibujarEncabezado("Informacion del Sistema");

    tft.setTextSize(1);
    int y = 42;

    auto dibujarFila = [&](const char* etiqueta, const char* valor, uint16_t color = C_TEXTO_PRINCIPAL) {
        tft.setTextColor(C_TEXTO_SECUNDARIO);
        tft.setCursor(12, y);  tft.print(etiqueta);
        tft.setTextColor(color);
        tft.setCursor(100, y); tft.print(valor);
        y += 15;
    };

    dibujarFila("SO:",      "Luvian OS v5.0");
    dibujarFila("CPU:",     "ESP32 @ 240MHz");
    dibujarFila("Flash:",   "4MB");
    dibujarFila("RAM:",     "520KB SRAM");
    dibujarFila("Pantalla:", "ILI9341 320x240");
    dibujarFila("Touch:",   "XPT2046 SPI");
    dibujarFila("SD:",      sdLista ? "Conectada" : "No detectada",
            sdLista ? (uint16_t)C_EXITO : (uint16_t)C_ERROR);
    dibujarFila("Sensor:",  "DHT11 (GPIO 16)");
    dibujarFila("LED:",     "GPIO 17");
    dibujarFila("Buzzer:",  "GPIO 27");
    dibujarFila("Apps:",    "10 aplicaciones");

    y += 5;
    tft.setTextColor(C_TEXTO_SECUNDARIO);
    tft.setCursor(12, y);
    tft.print("RAM Libre:");
    uint32_t ramLibre = obtenerMemoriaLibre();
    uint32_t ramTotal = obtenerMemoriaTotal();
    int porcentaje = (ramLibre * 100) / ramTotal;
    dibujarBarraProgreso(100, y - 5, 200, 10, porcentaje, 100, C_MARCA_PRIMARIO);
    y += 18;

    char ramStr[20];
    formatearBytes(ramLibre, ramStr, sizeof(ramStr));
    tft.setTextColor(C_TEXTO_TERCIARIO);
    tft.setCursor(12, y);
    tft.print(ramStr);
    tft.print(" / ");
    formatearBytes(ramTotal, ramStr, sizeof(ramStr));
    tft.print(ramStr);

    dibujarTarjeta(250, 170, 60, 22, C_BOTON_INACTIVO);
    tft.drawRect(250, 170, 60, 22, C_BORDE_ACTIVO);
    tft.setTextColor(C_MARCA_PRIMARIO);
    tft.setTextSize(1);
    tft.setCursor(258, 177);
    tft.print("MEM >");
}

void manejarInfo(int x, int y) {
    if (manejarBotonVolverUniversal(x, y)) return;
    if (enRectangulo(x, y, 250, 170, 60, 22)) {
        beepBoton();
        renderizarMemoria();
    }
}
