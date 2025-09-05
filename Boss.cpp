#include "Boss.h"
#include <cstdlib> // rand()

void Boss::Initialize(Input* input) {
    input_ = input;
	// �e�N�X�`���̓ǂݍ���
    bossTexture_ = TextureManager::Load("slimeKing.png");
    bossDamegeTexture_ = TextureManager::Load("slimeKing_Dmaege.png");
	// HP�Q�[�W
    hpBackTex_ = TextureManager::Load("BossHpBack.png");
    hpGaugeTex_ = TextureManager::Load("BossHpRed.png");
    hpBackSprite_.reset(Sprite::Create(hpBackTex_, { 400, 20 }));
    hpGaugeSprite_.reset(Sprite::Create(hpGaugeTex_, { 400, 20 }));
    hpBackSprite_->SetSize({ 480, 20 });   // �w�i�o�[�̃T�C�Y
    hpGaugeSprite_->SetSize({ 480, 20 });  // �Q�[�W�ő�T�C�Y

	// �X�v���C�g�̐����Ə����ʒu�ݒ�
    basePos_ = { 540.0f, 40.0f };
    bossSprite_.reset(Sprite::Create(bossTexture_, basePos_));
    bossDamegeSprite_.reset(Sprite::Create(bossDamegeTexture_, basePos_));
    bossSprite_->SetPosition(basePos_);
    bossDamegeSprite_->SetPosition(basePos_);
    maxHp_ = 100;
    currentHp_ = maxHp_;


}

void Boss::Update() {
    if (isShaking_) {
        shakeTimer_--;
        if (shakeTimer_ <= 0) {
            isShaking_ = false;
            bossSprite_->SetPosition(basePos_);
			bossDamegeSprite_->SetPosition(basePos_);
        }
        else {
            // �����_���ɗh�炷
            float offsetX = (rand() % 100 / 100.0f - 0.5f) * 2 * shakeStrength_;
            float offsetY = (rand() % 100 / 100.0f - 0.5f) * 2 * shakeStrength_;
            bossSprite_->SetPosition({ basePos_.x + offsetX, basePos_.y + offsetY });
			bossDamegeSprite_->SetPosition({ basePos_.x + offsetX, basePos_.y + offsetY });
        }
    }

    /*if (input_->PushKey(DIK_1)) { 
        if (!isDebugdamage_) {
            OnDamage();
            isDebugdamage_ = true;
        }
    }
    else if(input_->PushKey(DIK_2)){
		isDebugdamage_ = false;
    }*/
	// �f�o�b�O�p�F1�L�[��10�_���[�W
    if (input_->PushKey(DIK_1)) {
        TakeDamage(10);
    }
}

void Boss::Draw() {
    if (bossSprite_&&!isShaking_) {
        bossSprite_->Draw();
    }
    if (isShaking_ && bossDamegeSprite_) {
        bossDamegeSprite_->Draw();
	}
    // HP�Q�[�W��`��
    if (hpBackSprite_) {
        hpBackSprite_->Draw();
    }
    if (hpGaugeSprite_) {
        float hpPercent = (float)currentHp_ / maxHp_;
        if (hpPercent < 0.0f) hpPercent = 0.0f;

        // ������HP�����ɉ����ďk�߂�
        hpGaugeSprite_->SetSize({ 480 * hpPercent, 20 });
        hpGaugeSprite_->SetPosition({ 400, 20 });

        hpGaugeSprite_->Draw();
    }
}

// �� �_���[�W���󂯂��Ƃ��ɌĂԊ֐�
void Boss::OnDamage() {
    isShaking_ = true;
    shakeTimer_ = 20;  // �h���t���[����
}

void Boss::TakeDamage(int damage) {
    if (isDead_) return;

    currentHp_ -= damage;
    if (currentHp_ < 0) currentHp_ = 0;

    // �f�o�b�O�o�͂Ŋm�F
    printf("Boss HP: %d / %d (Damage %d)\n", currentHp_, maxHp_, damage);

    if (currentHp_ == 0) {
        isDead_ = true;
        // �|�ꂽ���o�Ȃǂ�������
    }
    else {
        OnDamage(); // �_���[�W���o�i�V�F�C�N�j
    }
}
