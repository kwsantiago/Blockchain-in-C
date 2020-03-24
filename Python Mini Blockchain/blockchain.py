from block import Block
import datetime

blockchain = [Block.create_genesis_block()]

print("The Genesis Block has been created!\n")
print("Hash: %s" % blockchain[-1].hash)

num_blocks_to_add = 10

for i in range(1, num_blocks_to_add+1):
    blockchain.append(Block(blockchain[-1].hash,
                            "data",
                            datetime.datetime.now()))

    print("Block #%d has been created" % i)
    print("Block #%d hash: %s" % (i, blockchain[i].hash))

