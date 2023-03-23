/**
 * @file jiffies_timer.h
 * @brief O(1)���Ӷȶ�ʱ������Ʋο�linux kernel(4.9.10)��jiffies timer
 * @see https://git.kernel.org/cgit/linux/kernel/git/stable/linux-stable.git/tree/kernel/time/timer.c
 * Licensed under the MIT licenses.
 *
 * @note ���Ը���ʵ����Ҫ�Զ���ÿ��tick�ļ��,���е��㷨������tickΪ��λ��
 *       4.9.10�汾��jiffies_timer��Ϊ8-9����ʱ����ÿ���������2^3�������ж�ʱ���б��д����һ��2^6*[8-9]=512-576����ʱ���б�
 *       ���ڱ���ʱ������ʵ�֣���������Ӳ��ʱ�ӣ��������tick���ȺܸߵĻ������Ƚϴ����������ֱ��ʹ��kernel��timer����Ϊ�ں˰汾������Ӳ��ʱ��
 * @version 1.0
 * @author owent
 * @date 2017-02-16
 * @history
 *      2017-02-17: ��һ��ʵ�֣���ʱ������
 */

/**
 * from: https://github.com/atframework/atframe_utils/blob/main/include/time/jiffies_timer.h
 */

#ifndef UTIL_TIME_JIFFIES_TIMER_H
#define UTIL_TIME_JIFFIES_TIMER_H

#pragma once

 /**
  * ���Ȳο�
  * HZ 1000 steps, LVL_BITS=6,LVL_CLK_SHIFT=3,LVL_DEPTH=9
  * Level Offset  Granularity            Range
  *  0      0         1 ms                0 ms -         63 ms
  *  1     64         8 ms               64 ms -        511 ms
  *  2    128        64 ms              512 ms -       4095 ms (512ms - ~4s)
  *  3    192       512 ms             4096 ms -      32767 ms (~4s - ~32s)
  *  4    256      4096 ms (~4s)      32768 ms -     262143 ms (~32s - ~4m)
  *  5    320     32768 ms (~32s)    262144 ms -    2097151 ms (~4m - ~34m)
  *  6    384    262144 ms (~4m)    2097152 ms -   16777215 ms (~34m - ~4h)
  *  7    448   2097152 ms (~34m)  16777216 ms -  134217727 ms (~4h - ~1d)
  *  8    512  16777216 ms (~4h)  134217728 ms - 1073741822 ms (~1d - ~12d)
  *
  * HZ  250, LVL_BITS=6,LVL_CLK_SHIFT=3,LVL_DEPTH=9
  * Level Offset  Granularity            Range
  *  0	   0         4 ms                0 ms -        255 ms
  *  1	  64        32 ms              256 ms -       2047 ms (256ms - ~2s)
  *  2	 128       256 ms             2048 ms -      16383 ms (~2s - ~16s)
  *  3	 192      2048 ms (~2s)      16384 ms -     131071 ms (~16s - ~2m)
  *  4	 256     16384 ms (~16s)    131072 ms -    1048575 ms (~2m - ~17m)
  *  5	 320    131072 ms (~2m)    1048576 ms -    8388607 ms (~17m - ~2h)
  *  6	 384   1048576 ms (~17m)   8388608 ms -   67108863 ms (~2h - ~18h)
  *  7	 448   8388608 ms (~2h)   67108864 ms -  536870911 ms (~18h - ~6d)
  *  8    512  67108864 ms (~18h) 536870912 ms - 4294967288 ms (~6d - ~49d)
  *
  * HZ  100, LVL_BITS=6,LVL_CLK_SHIFT=3,LVL_DEPTH=8
  * Level Offset  Granularity            Range
  *  0	   0         10 ms               0 ms -        630 ms
  *  1	  64         80 ms             640 ms -       5110 ms (640ms - ~5s)
  *  2	 128        640 ms            5120 ms -      40950 ms (~5s - ~40s)
  *  3	 192       5120 ms (~5s)     40960 ms -     327670 ms (~40s - ~5m)
  *  4	 256      40960 ms (~40s)   327680 ms -    2621430 ms (~5m - ~43m)
  *  5	 320     327680 ms (~5m)   2621440 ms -   20971510 ms (~43m - ~5h)
  *  6	 384    2621440 ms (~43m) 20971520 ms -  167772150 ms (~5h - ~1d)
  *  7	 448   20971520 ms (~5h) 167772160 ms - 1342177270 ms (~1d - ~15d)
  *
  * HZ  10, LVL_BITS=8,LVL_CLK_SHIFT=3,LVL_DEPTH=8
  * Level Offset  Granularity              Range
  *  0	   0        100 ms                 0 ms -       25500 ms (0s - ~25s)
  *  1	 256        800 ms             25600 ms -      204700 ms (25s - ~204s)
  *  2	 512       6400 ms (~6s)      204800 ms -     1638300 ms (~204s - ~27m)
  *  3	 768      51200 ms (~51s)    1638400 ms -    13107100 ms (~27m - ~3h)
  *  4   1024     409600 ms (~409s)  13107200 ms -   104857500 ms (~3h - ~29h)
  *  5   1280    3276800 ms (~55m)  104857600 ms -   838860700 ms (~29h - ~9d)
  *  6   1536   26214400 ms (~7h)   838860800 ms -  6710886300 ms (~9d - ~77d)
  *  7   1792  209715200 ms (~58h) 6710886400 ms - 13421772700 ms (~19d - ~621d)
  */

//#include <config/compiler_features.h>

//#include <config/atframe_utils_build_feature.h>

#ifndef LIBATFRAME_UTILS_NAMESPACE_BEGIN
#define LIBATFRAME_UTILS_NAMESPACE_BEGIN
#define LIBATFRAME_UTILS_NAMESPACE_END
#define LIBATFRAME_UTILS_API_HEAD_ONLY
#endif

#define UTIL_CONFIG_STATIC_ASSERT(X) static_assert(X, #X)

#include <assert.h>
#include <stdint.h>
#include <bitset>
#include <cstddef>
#include <cstring>
#include <ctime>
#include <functional>
#include <list>
#include <memory>

LIBATFRAME_UTILS_NAMESPACE_BEGIN
namespace timer_namespace {
    /**
     * @brief jiffies timer ��ʱ��ʵ��
     * @note �ռ临�Ӷ�: O(LVL_DEPTH * 2^LVL_BITS * sizeof(std::list)) <br />
     *       ÿ��tick�����ʱ�临�Ӷ�: O(LVL_DEPTH) <br />
     *       ÿ�㶨ʱ������: 2^LVL_CLK_SHIFT <br />
     *       ���ʱ����Χ: 2^(LVL_CLK_SHIFT * (LVL_DEPTH - 1) + LVL_BITS) * tick���� <br />
     * @note ����ⲿ��Ҫ���ö�ʱ��������ʹ�� timer_t ���溯��ǩ���е� timer_type
     */
    template <time_t LVL_BITS = 6, time_t LVL_CLK_SHIFT = 3, size_t LVL_DEPTH = 8>
    class LIBATFRAME_UTILS_API_HEAD_ONLY jiffies_timer {
    public:
        UTIL_CONFIG_STATIC_ASSERT(LVL_CLK_SHIFT < LVL_BITS);

        enum lvl_clk_consts {
            LVL_CLK_DIV = 1 << LVL_CLK_SHIFT,
            LVL_CLK_MASK = LVL_CLK_DIV - 1,
        };
        static inline time_t LVL_SHIFT(time_t n) { return n * LVL_CLK_SHIFT; }

        static inline time_t LVL_GRAN(time_t n) { return static_cast<time_t>(1) << LVL_SHIFT(n); }

        enum lvl_consts {
            LVL_SIZE = 1 << LVL_BITS,  //
            LVL_MASK = LVL_SIZE - 1,
            WHEEL_SIZE = LVL_SIZE * LVL_DEPTH
        };
        static inline size_t LVL_OFFS(size_t n) { return n * LVL_SIZE; }

        static inline time_t LVL_START(size_t n) { return static_cast<time_t>((LVL_SIZE) << ((n - 1) * LVL_CLK_SHIFT)); }

    private:
        struct timer_type;

    public:

        using timer_callback_fn_t = std::function<void(time_t tick_time, const timer_type& timer)>;
        using timer_ptr_t = std::shared_ptr<timer_type>;  // �ⲿ����ֱ�ӷ����ڲ���Ա��ֻ����ͨ��API����
        using timer_wptr_t = std::weak_ptr<timer_type>;   // �ⲿ����ֱ�ӷ����ڲ���Ա��ֻ����ͨ��API����

    private:

        struct timer_type {
            mutable uint32_t flags;                                // ��ʱ�����λ
            uint32_t sequence;                                     // ��ʱ�����
            time_t timeout;                                        // ԭʼ�ĳ�ʱʱ��
            void* private_data;                                    // ˽������ָ��
            timer_callback_fn_t fn;                                // �ص�����
            jiffies_timer* owner;                                  // �����Ķ�ʱ��������
            std::list<timer_ptr_t>* owner_round;                   // ������ʱ����
            typename std::list<timer_ptr_t>::iterator owner_iter;  // ������ʱ���ֵ�����
        };  // �ⲿ����ֱ�ӷ����ڲ���Ա��ֻ����ͨ��API����

    public:
        using timer_t = timer_type;  // �ⲿ����ֱ�ӷ����ڲ���Ա��ֻ����ͨ��API����

        struct flag_t {
            enum type {
                EN_JTFT_INITED = 0,
                EN_JTFT_MAX,
            };
        };

        struct timer_flag_t {
            enum type {
                EN_JTTF_DISABLED = 0x0001,
                EN_JTTF_REMOVED = 0x0002,  // readonly flag
            };
        };

        struct error_type_t {
            enum type {
                EN_JTET_SUCCESS = 0,              // �ɹ�
                EN_JTET_NOT_INITED = -101,        // δ��ʼ��
                EN_JTET_ALREADY_INITED = -102,    // �ѳ�ʼ��
                EN_JTET_TIMEOUT_EXTENDED = -103,  // ��ʱʱ�䳬������
            };
        };

    public:
        /**
         * @brief ��ʼ����ʱ��
         * @param init_tick ��ʼ��ʱ��tick��������ʱ�䣩����ʱ���������ʱ�俪ʼ����
         * @return 0�������
         */
        int init(time_t init_tick) {
            if (flags_.test(flag_t::EN_JTFT_INITED)) {
                return error_type_t::EN_JTET_ALREADY_INITED;
            }
            flags_.set(flag_t::EN_JTFT_INITED, true);

            last_tick_ = init_tick;
            seq_alloc_ = 0;
            size_ = 0;

            return error_type_t::EN_JTET_SUCCESS;
        }

        /**
         * @brief ��Ӷ�ʱ��
         * @param delta ��ʱ����������ʱ�䣨����ȡ���������Ӧ����3.8����tick����������Ӧ��ȡ3��
         * @param fn ��ʱ���ص�����
         * @param priv_data
         * @param watcher ��ʱ���ļ�����ָ�룬����ǿգ����weak_ptr��ָ��ʱ�����������Ժ��ѯ���޸�����
         * @note ��ʱ���ص���֤����ָ��ʱ���������һ����Χ��ʱ�䴥����
         *       ������һ��������������Ϊ��ǰtick��ʱ���ѱ�����ȡ��������3.8��tick��ʱ���ڶ�ʱ�����¼����3��
         *       ���Իᱣ֤��ʱ���Ĵ���ʱ��һ������ָ����ʱ�䣨����3.8+2=5.8��ζ�ŵ�6��tick�Żᴥ����ʱ����
         * @note �뾡����Ҫ���ⲿֱ�ӱ��涨ʱ��������ָ��(timer_ptr_t)��������ʹ�ü�����
         * @return 0�������
         */
        template <class TCALLBACK>
        inline int add_timer(time_t delta, TCALLBACK&& fn, void* priv_data, timer_wptr_t* watcher) {
            return add_timer(delta, timer_callback_fn_t(std::forward<TCALLBACK>(fn)), priv_data, watcher);
        }

        int add_timer(time_t delta, timer_callback_fn_t&& fn, void* priv_data, timer_wptr_t* watcher) {
            if (!flags_.test(flag_t::EN_JTFT_INITED)) {
                return error_type_t::EN_JTET_NOT_INITED;
            }

            if (delta > get_max_tick_distance()) {
                return error_type_t::EN_JTET_TIMEOUT_EXTENDED;
            }

            if (!fn) {
                return error_type_t::EN_JTET_SUCCESS;
            }

            // must greater than 0
            if (delta < 0) {
                delta = 0;
            }

            timer_ptr_t timer_inst = std::make_shared<timer_type>();
            timer_inst->flags = 0;
            timer_inst->timeout = last_tick_ + delta;
            timer_inst->private_data = priv_data;
            timer_inst->owner_round = nullptr;
            timer_inst->owner = this;
            // timer_inst->owner_iter = ...
            while (0 == ++seq_alloc_)
                ;
            timer_inst->sequence = seq_alloc_;

            size_t idx = calc_wheel_index(timer_inst->timeout, last_tick_);
            assert(idx < WHEEL_SIZE);

            timer_inst->fn = std::move(fn);

            // assign to watcher
            if (watcher != nullptr) {
                *watcher = timer_inst;
            }
            timer_inst->owner_iter = timer_base_[idx].insert(timer_base_[idx].end(), timer_inst);
            timer_inst->owner_round = &timer_base_[idx];
            ++size_;

            return error_type_t::EN_JTET_SUCCESS;
        }

        inline int add_timer(time_t delta, const timer_callback_fn_t& fn, void* priv_data) {
            return add_timer(delta, fn, priv_data, nullptr);
        }

        inline int add_timer(time_t delta, timer_callback_fn_t&& fn, void* priv_data) {
            return add_timer(delta, fn, priv_data, nullptr);
        }

        /**
         * @brief ��ʱ���δ�
         * @param expires ���ڵĶ�ʱ��ʱ�䣨����ʱ�䣩
         * @return ������򴥷��Ķ�ʱ������
         */
        int tick(time_t expires) {
            std::list<timer_ptr_t>* timer_list[LVL_DEPTH];
            int ret = 0;

            if (!flags_.test(flag_t::EN_JTFT_INITED)) {
                return error_type_t::EN_JTET_NOT_INITED;
            }

            if (expires <= last_tick_) {
                return ret;
            }

            while (last_tick_ < expires) {
                ++last_tick_;

                size_t list_sz = collect_expired_timers(last_tick_, timer_list);
                while (list_sz > 0) {
                    --list_sz;

                    /* �Ӹ߲㼶���Ͳ㼶�ߣ������ܱ�֤��ʱ��ʱ�� */
                    if (timer_list[list_sz]->empty()) {
                        continue;
                    }

                    typename std::list<timer_ptr_t>::iterator last_iter = timer_list[list_sz]->end();
                    --last_iter;
                    bool consume_next = true;
                    for (typename std::list<timer_ptr_t>::iterator iter = timer_list[list_sz]->begin(); consume_next;) {
                        /* �ڶ�ʱ���ص������п��ܵ���remove_timer���õ�ǰ������ʧЧ
                           ����������뱣�涨ʱ������ָ�룬Ȼ��ֱ�ӹ�������һ������Ϊ��ǰ����������ʧЧ*/
                        timer_ptr_t timer_ptr = *iter;
                        consume_next = iter != last_iter;
                        ++iter;
                        if (timer_ptr) {
                            if (timer_ptr->fn && !(timer_ptr->flags & timer_flag_t::EN_JTTF_DISABLED)) {
                                timer_ptr->fn(last_tick_, *timer_ptr);
                                ++ret;
                            }

                            remove_timer(*timer_ptr);
                        }
                    }
                }
            }

            return ret;
        }

        /**
         * @brief ��ȡ���һ�ζ�ʱ���δ�ʱ�䣨��ǰ��ʱ��ʱ�䣩
         * @return ���һ�ζ�ʱ���δ�ʱ�䣨��ǰ��ʱ��ʱ�䣩
         */
        inline time_t get_last_tick() const { return last_tick_; }

        /**
         * @brief ��ȡ���һ�ζ�ʱ���δ�ʱ�䣨��ǰ��ʱ��ʱ�䣩
         * @return ���һ�ζ�ʱ���δ�ʱ�䣨��ǰ��ʱ��ʱ�䣩
         */
        inline size_t size() const { return size_; }

    public:
        /**
         * @brief ��ȡ��ǰ��ʱ�����͵����ʱ�䷶Χ��tick��
         * @return ��ǰ��ʱ�����͵����ʱ�䷶Χ��tick��
         */
        static inline constexpr time_t get_max_tick_distance() { return LVL_START(LVL_DEPTH) - 1; }

        static inline size_t calc_index(time_t expires, size_t lvl) {
            /* �����expires ��Ȼ���ڵ���last_tick_���������ټ�һ֡
               ��֡�Ķ�ʱ���б�����ܻ���ִ�У����Բ��ܼ��ڵ�ǰ֡ */
            expires = (expires + LVL_GRAN(lvl)) >> LVL_SHIFT(lvl);
            return LVL_OFFS(lvl) + static_cast<size_t>(expires & LVL_MASK);
        }

        static size_t calc_wheel_index(time_t expires, time_t clk) {
            assert(expires >= clk);
            time_t delta = expires - clk;
            size_t idx = WHEEL_SIZE;

            for (size_t lvl = 0; lvl < LVL_DEPTH; ++lvl) {
                if (delta < LVL_START(lvl + 1)) {
                    idx = calc_index(expires, lvl);
                    break;
                }
            }

            assert(idx < WHEEL_SIZE);
            return idx;
        }

    public:
        static inline void* get_timer_private_data(const timer_type& timer) { return timer.private_data; }
        static inline void* set_timer_private_data(timer_type& timer, void* priv_data) {
            void* old_value = timer.private_data;
            timer.private_data = priv_data;
            return old_value;
        }
        static inline uint32_t get_timer_sequence(const timer_type& timer) { return timer.sequence; }
        static inline bool check_timer_flags(const timer_type& timer, typename timer_flag_t::type f) {
            return !!(timer.flags & static_cast<uint32_t>(f));
        }
        static inline void set_timer_flags(const timer_type& timer, typename timer_flag_t::type f) {
            timer.flags |= static_cast<uint32_t>(f);
        }
        static inline void unset_timer_flags(const timer_type& timer, typename timer_flag_t::type f) {
            timer.flags &= ~static_cast<uint32_t>(f);
        }
        static inline void remove_timer(timer_type& timer) {
            if (nullptr != timer.owner_round) {
                if (timer.owner_iter != timer.owner_round->end()) {
                    timer.owner_round->erase(timer.owner_iter);
                }

                timer.owner_iter = timer.owner_round->end();
                timer.owner_round = nullptr;
            }

            if (nullptr != timer.owner) {
                --timer.owner->size_;
                timer.owner = nullptr;
            }

            set_timer_flags(timer, timer_flag_t::EN_JTTF_REMOVED);
        }

    private:
        size_t collect_expired_timers(time_t tick_time, std::list<timer_ptr_t>* timer_list[LVL_DEPTH]) {
            size_t ret = 0;
            for (size_t i = 0; i < LVL_DEPTH; ++i) {
                size_t idx = static_cast<size_t>(tick_time & LVL_MASK) + LVL_OFFS(i);

                if (!timer_base_[idx].empty()) {
                    timer_list[ret++] = &timer_base_[idx];
                }

                if (tick_time & LVL_CLK_MASK) {
                    break;
                }

                tick_time >>= LVL_CLK_SHIFT;
            }

            return ret;
        }

    private:
        time_t last_tick_;
        std::bitset<flag_t::EN_JTFT_MAX> flags_;
        std::list<timer_ptr_t> timer_base_[WHEEL_SIZE];
        uint32_t seq_alloc_;
        size_t size_;
    };
}  // namespace time
LIBATFRAME_UTILS_NAMESPACE_END

#endif  // _UTIL_TIME_TIME_UTILITY_H_