#ifndef ORDER_H
#define ORDER_H

namespace Gazua {
    class Order;
};

class Gazua::Order {
private:
    std::string currency_pair,		// �ش� ��ȭ��
                side;				// �ż�/�ŵ� ���� (�ż�: bid, �ŵ�: ask)
    uint64_t    avg_price,			// ü�� ������ ���� ���ġ
                price;				// �ֹ� �ÿ� ������ ������, �⺻���� 0 
    long double order_amount,		// �ֹ� �ÿ� ������ ������ ����
                filled_amount,		// ������� ü��� ������ ����
    uint64_t    order_total,		// �ֹ� �ݾ�
                filled_total,		// ü�� �ݾ�
                created_at,			// �ŷ��� �ֹ��� �ð� Unix timestamp(milliseconds)
                last_filled_at;		// �ŷ��� �κ� ü��� ���� �ð� Unix timestamp(milliseconds)
    std::string status;				// ���� �ֹ��� ���� ('unfilled', 'partially_filled', 'filled')
    long double fee;				// �ŷ� ������
    // id(�ֹ��� ID �ĺ���ȣ)�� map �ڷ������� key������ ��� ����
public:		

}

#endif�� 
