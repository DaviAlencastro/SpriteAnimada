
#include "CharacterController.h"

CharacterController::CharacterController(GLFWwindow* win, GLuint shaderID)
    : janela(win),
      spriteFrente("imagens/D_Walk.png", 1, 3),
      spriteCosta("imagens/U_Walk.png", 1, 3),
      spriteEsquerda("imagens/L_Walk.png", 1, 3),
      spriteDireita("imagens/R_Walk.png", 1, 3),
      spriteFrenteIdle("imagens/D_Idle.png", 1, 2),
      spriteCostaIdle("imagens/U_Idle.png", 1, 2),
      spriteEsquerdaIdle("imagens/L_Idle.png", 1, 2),
      spriteDireitaIdle("imagens/R_Idle.png", 1, 2),
      posicao(400.0f, 300.0f),
      velocidade(100.0f)
{
    // Setar shader para todos os sprites
    spriteFrente.setShader(shaderID);
    spriteCosta.setShader(shaderID);
    spriteEsquerda.setShader(shaderID);
    spriteDireita.setShader(shaderID);

    spriteFrenteIdle.setShader(shaderID);
    spriteCostaIdle.setShader(shaderID);
    spriteEsquerdaIdle.setShader(shaderID);
    spriteDireitaIdle.setShader(shaderID);

    spriteAtual = &spriteFrenteIdle;  // Começa parado
}

void CharacterController::atualizar(float deltaTime) {
    glm::vec2 direcao(0.0f);

    static SpriteAnimado* ultimaAnimacao = &spriteFrenteIdle;

if (glfwGetKey(janela, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(janela, GLFW_KEY_UP) == GLFW_PRESS) {
    direcao.y -= 1;
    ultimaAnimacao = &spriteCosta;
}
else if (glfwGetKey(janela, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(janela, GLFW_KEY_DOWN) == GLFW_PRESS) {
    direcao.y += 1;
    ultimaAnimacao = &spriteFrente;
}
else if (glfwGetKey(janela, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(janela, GLFW_KEY_LEFT) == GLFW_PRESS) {
    direcao.x -= 1;
    ultimaAnimacao = &spriteEsquerda;
}
else if (glfwGetKey(janela, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(janela, GLFW_KEY_RIGHT) == GLFW_PRESS) {
    direcao.x += 1;
    ultimaAnimacao = &spriteDireita;
}

if (direcao != glm::vec2(0.0f)) {
    posicao += direcao * velocidade * deltaTime;
    spriteAtual = ultimaAnimacao;
    spriteAtual->atualizar(deltaTime);
} else {
    // Mapeia qual Idle usar com base na última animação
    if (ultimaAnimacao == &spriteFrente)      spriteAtual = &spriteFrenteIdle;
    else if (ultimaAnimacao == &spriteCosta)  spriteAtual = &spriteCostaIdle;
    else if (ultimaAnimacao == &spriteEsquerda) spriteAtual = &spriteEsquerdaIdle;
    else if (ultimaAnimacao == &spriteDireita)  spriteAtual = &spriteDireitaIdle;
}

}

void CharacterController::desenhar() {
    if (spriteAtual == &spriteFrenteIdle || spriteAtual == &spriteCostaIdle ||
        spriteAtual == &spriteEsquerdaIdle || spriteAtual == &spriteDireitaIdle) {
        spriteAtual->desenhar(posicao, glm::vec2(70.0f, 70.0f));  // escala menor para idle
    } else {
        spriteAtual->desenhar(posicao, glm::vec2(64.0f, 64.0f));  // escala normal para walk
    }
}
