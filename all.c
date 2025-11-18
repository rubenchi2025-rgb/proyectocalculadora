#include <stdio.h>
#include <math.h>

// Constantes de conversión
#define DB_POTENCIA 10.0 // dB para potencias
#define DB_TENSION 20.0 // dB para tensiones
#define V_REF_DBUV 1.0 // Referencia 1 µV (usada en dBµV, pero como 1)

// Prototipos
double mw_a_dbm(double mW);
double dbm_a_mW(double dBm);
double w_a_dbw(double W);
double dbw_a_W(double dBW);
double v_a_dbv(double V);
double dbv_a_V(double dBV);
double uV_a_dbuV(double uV);
double dbuV_a_uV(double dbuV);
double calcular_ganancia_db(double salida, double entrada, int tipo);

int leer_opcion(void);
double leer_valor_positivo(const char *mensaje);
void limpiar_buffer(void);

// Programa principal
int main() {
    int opcion, modo_conversion;
    double valor, resultado;

    do {
        printf("\n=== CALCULADORA TELECO ===\n");
        printf("1) Potencia: mW ↔ dBm\n");
        printf("2) Potencia: W  ↔ dBW\n");
        printf("3) Tensión : V  ↔ dBV\n");
        printf("4) Tensión : µV ↔ dBµV\n");
        printf("5) Ganancia/Atenuación (dB)\n");
        printf("6) Salir\n");
        printf("Elige una opción: ");

        opcion = leer_opcion();

        if (opcion == 1 || opcion == 2 || opcion == 3 || opcion == 4) {
            printf("\nIndica el tipo de conversión:\n1) Lineal a dB\n2) dB a Lineal\nElige opción: ");
            modo_conversion = leer_opcion();

            if (modo_conversion != 1 && modo_conversion != 2) {
                printf("Opción de conversión no válida.\n");
                continue;
            }

            switch (opcion) {
                case 1: // mW ↔ dBm
                    if (modo_conversion == 1) {
                        valor = leer_valor_positivo("Introduce potencia en mW: ");
                        resultado = mw_a_dbm(valor);
                        printf("%.3f mW = %.3f dBm\n", valor, resultado);
                    } else {
                        printf("Introduce valor en dBm: ");
                        if (scanf("%lf", &valor) == 1) {
                            limpiar_buffer();
                            resultado = dbm_a_mW(valor);
                            printf("%.3f dBm = %.3f mW\n", valor, resultado);
                        } else {
                            printf("Entrada no válida. Inténtalo de nuevo.\n");
                            limpiar_buffer();
                        }
                    }
                    break;
                case 2: // W ↔ dBW
                    if (modo_conversion == 1) {
                        valor = leer_valor_positivo("Introduce potencia en W: ");
                        resultado = w_a_dbw(valor);
                        printf("%.3f W = %.3f dBW\n", valor, resultado);
                    } else {
                        printf("Introduce valor en dBW: ");
                        if (scanf("%lf", &valor) == 1) {
                            limpiar_buffer();
                            resultado = dbw_a_W(valor);
                            printf("%.3f dBW = %.3f W\n", valor, resultado);
                        } else {
                            printf("Entrada no válida. Inténtalo de nuevo.\n");
                            limpiar_buffer();
                        }
                    }
                    break;
                case 3: // V ↔ dBV
                    if (modo_conversion == 1) {
                        valor = leer_valor_positivo("Introduce tensión en V: ");
                        resultado = v_a_dbv(valor);
                        printf("%.3f V = %.3f dBV\n", valor, resultado);
                    } else {
                        printf("Introduce valor en dBV: ");
                        if (scanf("%lf", &valor) == 1) {
                            limpiar_buffer();
                            resultado = dbv_a_V(valor);
                            printf("%.3f dBV = %.3f V\n", valor, resultado);
                        } else {
                            printf("Entrada no válida. Inténtalo de nuevo.\n");
                            limpiar_buffer();
                        }
                    }
                    break;
                case 4: // µV ↔ dBµV
                    if (modo_conversion == 1) {
                        valor = leer_valor_positivo("Introduce tensión en µV: ");
                        resultado = uV_a_dbuV(valor);
                        printf("%.3f µV = %.3f dBµV\n", valor, resultado);
                    } else {
                        printf("Introduce valor en dBµV: ");
                        if (scanf("%lf", &valor) == 1) {
                            limpiar_buffer();
                            resultado = dbuV_a_uV(valor);
                            printf("%.3f dBµV = %.3f µV\n", valor, resultado);
                        } else {
                            printf("Entrada no válida. Inténtalo de nuevo.\n");
                            limpiar_buffer();
                        }
                    }
                    break;
                default:
                    printf("Error inesperado en el menú.\n");
            }
        } else if (opcion == 5) {
            double salida, entrada;
            int tipo;
            printf("\nGanancia/Atenuación (dB)\n");
            printf("Magnitud:\n1) Potencia\n2) Tensión\nElige tipo de magnitud: ");
            tipo = leer_opcion();

            if (tipo != 1 && tipo != 2) {
                printf("Opción no válida.\n");
                continue;
            }

            salida = leer_valor_positivo("Introduce valor de SALIDA: ");
            entrada = leer_valor_positivo("Introduce valor de ENTRADA: ");
            resultado = calcular_ganancia_db(salida, entrada, tipo);
            printf("Ganancia/Atenuación: %.3f dB\n", resultado);

        } else if (opcion == 6) {
            printf("Saliendo... ¡Hasta la próxima!\n");
        } else {
            printf("Opción no reconocida. Por favor, elige del 1 al 6.\n");
        }
        // El menú se repite automáticamente por el bucle
    } while (opcion != 6);

    return 0;
}

// Implementación de funciones

double mw_a_dbm(double mW) { // 1 mW referencia
    return DB_POTENCIA * log10(mW / 1.0);
}
double dbm_a_mW(double dBm) {
    return pow(10.0, dBm / DB_POTENCIA);
}
double w_a_dbw(double W) { // 1 W referencia
    return DB_POTENCIA * log10(W / 1.0);
}
double dbw_a_W(double dBW) {
    return pow(10.0, dBW / DB_POTENCIA);
}
double v_a_dbv(double V) { // 1 V referencia
    return DB_TENSION * log10(V / 1.0);
}
double dbv_a_V(double dBV) {
    return pow(10.0, dBV / DB_TENSION);
}
double uV_a_dbuV(double uV) { // 1 µV referencia
    return DB_TENSION * log10(uV / V_REF_DBUV);
}
double dbuV_a_uV(double dbuV) {
    return pow(10.0, dbuV / DB_TENSION) * V_REF_DBUV;
}

// tipo: 1 = potencia (10·log10), 2 = tensión (20·log10)
double calcular_ganancia_db(double salida, double entrada, int tipo) {
    if (entrada <= 0) { // Chequeo humano
        printf("El valor de entrada debe ser positivo (no cero ni negativo).\n");
        return 0.0;
    }
    if (salida <= 0) {
        printf("El valor de salida debe ser positivo.\n");
        return 0.0;
    }
    if (tipo == 2) // tensión
        return DB_TENSION * log10(salida / entrada);
    else
        return DB_POTENCIA * log10(salida / entrada);
}

//  Funciones de entrada/validación
int leer_opcion(void) {
    int op;
    if (scanf("%d", &op) != 1) {
        limpiar_buffer();
        return -1; 
    }
    limpiar_buffer();
    return op;
}

double leer_valor_positivo(const char *mensaje) {
    double val = -1;
    int ok = 0;
    while (!ok) {
        printf("%s", mensaje);
        if (scanf("%lf", &val) != 1) {
            printf("Entrada no válida. Inténtalo de nuevo.\n");
            limpiar_buffer();
        } else if (val <= 0) {
            printf("El valor debe ser positivo.\n");
            limpiar_buffer();
        } else {
            ok = 1;
            limpiar_buffer();
        }
    }
    return val;
}

// Limpia buffer tras scanf fallido
void limpiar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

